#!/usr/bin/env bash
# Build the libultra reference objects tools/libmatch.py compares against.
#
#   tools/build_ultralib.sh [<dir>]      (default: build/ultralib)
#
# Clones decompals/ultralib into <dir> and builds libultra_rom for every
# revision it knows (2.0D to 2.0L) with IDO 5.3 and ultralib's own flags.
# Matching against all of them is how the revision is identified
# (docs/LIBULTRA.md); the build is the same as Blast Corps'
# (../BlastCorps/tools/build_ultralib.sh).  The voice library (Japanese
# voice recognition, which this game doesn't link) fails to build on some
# hosts, so the build carries on past errors and only checks that the rest
# is there.
#
# Prints the object directories to pass to libmatch.py / gen_symbols.py,
# the one gen_symbols.py uses first.
set -euo pipefail

DIR=${1:-build/ultralib}
REV=e24c836796df4bf520ff8b11a5c9d2cea3a66cbd
VERSIONS="D E F G H I J K L"

if [ ! -d "$DIR/.git" ]; then
    git clone -q https://github.com/decompals/ultralib "$DIR"
fi
cd "$DIR"
git checkout -q "$REV"
make -C tools >/dev/null    # fetches IDO 5.3 (and the GCC tools ultralib also wants)

for v in $VERSIONS; do
    make -k -j"$(nproc)" VERSION="$v" TARGET=libultra_rom COMPARE=0 >"build-$v.log" 2>&1 || true
    for o in os/initialize io/vimgr libc/sprintf audio/synthesizer; do
        test -f "build/$v/libultra_rom/src/$o.o" || { echo "2.0$v: $o.o missing, see $DIR/build-$v.log" >&2; exit 1; }
    done
done

for v in $VERSIONS; do printf '%s ' "$PWD/build/$v/libultra_rom"; done
echo
