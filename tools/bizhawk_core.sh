#!/bin/sh
# Build BizHawk 2.8's own mupen64plus core and rsp-hle for Linux, as a
# reference for tools/tas.py (`tas.py run ... --bizhawk build/tas/bizhawk/dist`).
#
# BizHawk 2.8 runs N64 movies on its fork of mupen64plus (2013), which only
# builds for Windows: the emulation thread waits on a Win32 semaphore at
# every VI until the front end advances a frame.  A small shim stands in for
# that (and for SEH and MessageBox); the dynarec's fsqrt is renamed out of
# glibc's way; the window-hiding call in vidext goes; -ffast-math goes too
# (MSVC doesn't use it).  The source is BizHawk's tagged release tarball,
# sha256-pinned; nothing of it is committed.
#
# Needs: curl, a C compiler, make, SDL 1.2 headers (sdl12-compat), zlib,
# libpng, minizip.  Output: build/tas/bizhawk/dist/{libmupen64plus.so.2,
# mupen64plus-rsp-hle.so}.
set -e
ROOT=$(cd "$(dirname "$0")/.." && pwd)
B=$ROOT/build/tas/bizhawk
URL=https://codeload.github.com/TASEmulators/BizHawk/tar.gz/refs/tags/2.8
SHA256=61daf0695bebdce29e3f9f67fe062460b251f9b64ab70974e36b6a0f8f9094b5
mkdir -p "$B"
cd "$B"
if [ ! -f BizHawk-2.8.tar.gz ]; then
    curl -sSL "$URL" -o BizHawk-2.8.tar.gz.part
    mv BizHawk-2.8.tar.gz.part BizHawk-2.8.tar.gz
fi
echo "$SHA256  BizHawk-2.8.tar.gz" | sha256sum --check --quiet
rm -rf src
mkdir src
tar xzf BizHawk-2.8.tar.gz -C src --strip-components=2 \
    BizHawk-2.8/libmupen64plus/mupen64plus-core BizHawk-2.8/libmupen64plus/mupen64plus-rsp-hle
C=$B/src/mupen64plus-core
sed -i 's/^\t\tShowWindow(SysInfo.window,0);/\t\t;/' "$C/src/api/vidext.c"
sed -i 's/\bfsqrt\b/x86_fsqrt/g' "$C"/src/r4300/x86/*.[ch] "$C"/src/r4300/x86_64/*.[ch]
sed -i 's/ -ffast-math//' "$C/projects/unix/Makefile"

mkdir -p shim
cat > shim/Windows.h <<'EOF'
/* The little of Win32 that BizHawk's mupen64plus core uses. */
#ifndef BH_WINDOWS_SHIM_H
#define BH_WINDOWS_SHIM_H
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

typedef sem_t *HANDLE;
#define INFINITE 0xFFFFFFFFu

static inline HANDLE CreateSemaphore(void *attr, int initial, int max, void *name)
{
    sem_t *s = (sem_t *)malloc(sizeof *s);
    (void)attr, (void)max, (void)name;
    sem_init(s, 0, (unsigned)initial);
    return s;
}

static inline unsigned WaitForSingleObject(HANDLE h, unsigned timeout)
{
    (void)timeout;
    while (sem_wait(h) != 0)
        ;
    return 0;
}

static inline int ReleaseSemaphore(HANDLE h, int count, long *prev)
{
    (void)prev;
    while (count-- > 0)
        sem_post(h);
    return 1;
}

static inline int MessageBox(void *w, const char *text, const char *title, int flags)
{
    (void)w, (void)flags;
    fprintf(stderr, "%s: %s\n", title, text);
    return 0;
}

/* frontend.c's structured exception handling: just run the body */
#define __try if (1)
#define __except(x) else if (0)
#define EXCEPTION_EXECUTE_HANDLER 1
#endif
EOF

cd "$C/projects/unix"
CFLAGS="-I$B/shim -I$C/src/main/zip -include $B/shim/Windows.h -fcommon -Wno-error -Wno-implicit-function-declaration -Wno-int-conversion -Wno-incompatible-pointer-types -std=gnu99" \
    make all OSD=0 DEBUGGER=1 NO_ASM=1 OPTFLAGS=-O2 -j8 > "$B/core.log" 2>&1 \
    || { tail -40 "$B/core.log"; exit 1; }
cd "$B/src/mupen64plus-rsp-hle/projects/unix"
CFLAGS="-fcommon -Wno-error -std=gnu99" make all APIDIR="$C/src/api" -j8 > "$B/rsp.log" 2>&1 \
    || { tail -40 "$B/rsp.log"; exit 1; }
mkdir -p "$B/dist"
cp "$C/projects/unix/libmupen64plus.so.2.0.0" "$B/dist/libmupen64plus.so.2"
cp mupen64plus-rsp-hle.so "$B/dist/"
echo "$B/dist"
