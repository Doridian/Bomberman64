#!/usr/bin/env python3
"""Check that Hudson's allocator is GNU malloc's gmalloc.c, and generate its symbols.

    tools/libmalloc_check.py [--write] [us|eu|jp ...]

Downloads GNU malloc 1995 (https://ftp.gnu.org/old-gnu/malloc.tar.gz, sha256
pinned) into build/libmalloc/, compiles gmalloc.c with the repo's IDO 5.3 as
`-g -mips1 -G 0 -non_shared -DPAGESIZE=0x1000` (no source goes in the repo),
and compares the object's text with the ROM at 0xB3B70 (main_code, 0x22E0
bytes; jp's at 0xB3250) word for word. Only the fields a relocation fills are ignored (jal
targets, %hi/%lo halves). The relocations then give the address of every
function and variable, which must be the same wherever one symbol is
referenced twice. Exit status 1 on any mismatch.

--write writes symbol_addrs.libmalloc.<v>.txt (splat format). docs/LIBMALLOC.md
has the findings.

The stub headers written here are ours (stddef.h, limits.h, string.h,
sys/param.h): the compiler would otherwise read the host's /usr/include.
"""
import hashlib
import os
import re
import subprocess
import sys
import urllib.request

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
URL = "https://ftp.gnu.org/old-gnu/malloc.tar.gz"
SHA256 = "fa7353ea297e1e8e2a1a046583786c4adfbb581f5ec1c8980406b242a5da6ef1"
WORK = os.path.join(ROOT, "build", "libmalloc")
# where gmalloc's text starts in main_code (VRAM 0x80225800, ROM 0x40000):
# 0x80299370 in us and eu, 0x80298A50 in jp (whose main_code is shorter)
VRAMS = {"us": 0x80299370, "eu": 0x80299370, "jp": 0x80298A50}


def rom_off(version):
    return 0x40000 + VRAMS[version] - 0x80225800
TEXT_LEN = 0x22E0
OBJDUMP = "mips-linux-gnu-objdump"
READELF = "mips-linux-gnu-readelf"
OBJCOPY = "mips-linux-gnu-objcopy"

# gmalloc.c's static functions are not in the object's symbol table as such:
# the ROM's function boundaries (and the undefined align/initialize/morecore
# entries' sizes) give them.
STUBS = {
    "stddef.h": "#ifndef _STUB_STDDEF\n#define _STUB_STDDEF\ntypedef unsigned int size_t;\n"
                "typedef int ptrdiff_t;\n#ifndef NULL\n#define NULL 0\n#endif\n#endif\n",
    "limits.h": "#define CHAR_BIT 8\n",
    "string.h": "#include <stddef.h>\nextern void *memcpy(void *, const void *, size_t);\n"
                "extern void *memset(void *, int, size_t);\nextern void *memmove(void *, const void *, size_t);\n",
    "sys/param.h": "/* stub: PAGESIZE comes from -DPAGESIZE */\n",
}


def build():
    os.makedirs(WORK, exist_ok=True)
    tar = os.path.join(WORK, "malloc.tar.gz")
    if not os.path.exists(tar):
        with urllib.request.urlopen(URL) as r:
            data = r.read()
        if hashlib.sha256(data).hexdigest() != SHA256:
            sys.exit("malloc.tar.gz: sha256 mismatch")
        open(tar, "wb").write(data)
    elif hashlib.sha256(open(tar, "rb").read()).hexdigest() != SHA256:
        sys.exit("malloc.tar.gz: sha256 mismatch")
    subprocess.check_call(["tar", "xzf", tar, "-C", WORK])
    inc = os.path.join(WORK, "inc")
    for name, text in STUBS.items():
        p = os.path.join(inc, name)
        os.makedirs(os.path.dirname(p), exist_ok=True)
        open(p, "w").write(text)
    ido = os.path.join(ROOT, "tools", "ido", "5.3")
    env = dict(os.environ, USR_LIB=ido)
    obj = os.path.join(WORK, "gmalloc.o")
    src = os.path.join(WORK, "malloc")
    subprocess.check_call(
        [os.path.join(ido, "cc"), "-c", "-g", "-mips1", "-G", "0", "-non_shared",
         "-Xfullwarn", "-Xcpluscomm", "-D_LANGUAGE_C", "-DSTDC_HEADERS", "-DPAGESIZE=0x1000",
         "-Wab,-r4300_mul", "-woff", "649,838,712,807", "-I" + src, "-I" + inc,
         os.path.join(src, "gmalloc.c"), "-o", obj],
        env=env)
    return obj


def text_and_relocs(obj):
    bin_ = os.path.join(WORK, "gmalloc.text")
    subprocess.check_call([OBJCOPY, "-O", "binary", "-j", ".text", obj, bin_])
    text = open(bin_, "rb").read()
    out = subprocess.check_output([OBJDUMP, "-r", "-j", ".text", obj]).decode()
    rels = []
    for l in out.splitlines():
        m = re.match(r"([0-9a-f]+) (R_MIPS_\w+)\s+(\S+)", l.strip())
        if m:
            rels.append((int(m.group(1), 16), m.group(2), m.group(3)))
    return text, rels


def symtab(obj):
    funcs, objs = {}, {}
    for l in subprocess.check_output([READELF, "-sW", obj]).decode().splitlines():
        f = l.split()
        if len(f) < 8 or not f[0][:-1].isdigit():
            continue
        val, size, typ, ndx, name = int(f[1], 16), int(f[2]), f[3], f[6], f[7]
        if typ == "FUNC" and ndx != "UND":
            funcs[name] = (val, size)
        elif typ == "OBJECT":
            objs[name] = (val, size, ndx)
        elif typ == "NOTYPE" and ndx == "UND" and size:
            funcs[name] = (None, size)  # static function: size only
    return funcs, objs


def check(version, text, rels):
    off = rom_off(version)
    rom = open(os.path.join(ROOT, f"baserom.{version}.z64"), "rb").read()[off:off + len(text)]
    mask = {o: (0xFC000000 if t == "R_MIPS_26" else 0xFFFF0000) for o, t, _ in rels}
    bad = 0
    for i in range(0, len(text), 4):
        a = int.from_bytes(text[i:i + 4], "big")
        b = int.from_bytes(rom[i:i + 4], "big")
        m = mask.get(i, 0xFFFFFFFF)
        if a & m != b & m:
            bad += 1
            print(f"  {version}: +{i:#x} object {a:08x} ROM {b:08x}")
    print(f"{version}: {len(text):#x} bytes, {len(rels)} relocations, {bad} mismatching words")
    if bad:
        return None
    w = lambda o: int.from_bytes(rom[o:o + 4], "big")
    addr = {}  # symbol -> set of resolved addresses
    hi = {}
    for o, t, s in rels:
        if t == "R_MIPS_26":
            addr.setdefault(s, set()).add(((w(o) & 0x3FFFFFF) << 2) | 0x80000000)
        elif t == "R_MIPS_HI16":
            hi[s] = w(o) & 0xFFFF
        elif t == "R_MIPS_LO16":
            lo = w(o) & 0xFFFF
            lo -= 0x10000 if lo >= 0x8000 else 0
            addr.setdefault(s, set()).add((hi[s] << 16) + lo)
    return addr


def symbols(version, obj, addr):
    funcs, objs = symtab(obj)
    # a symbol's address is the same at every reference, and its base in
    # .text/.data/.bss follows from any one of them
    for s, a in addr.items():
        if s in objs or s in funcs:
            if len(a) != 1:
                sys.exit(f"{version}: {s} resolves to {sorted(a)}")
    out = []
    base = {}
    for n, (val, size, ndx) in objs.items():
        if n in addr:
            base[ndx] = list(addr[n])[0] - val
    # .data (section 5) and .bss (6): check the bases agree for every symbol
    for n, (val, size, ndx) in objs.items():
        if n in addr and list(addr[n])[0] - val != base[ndx]:
            sys.exit(f"{version}: {n} disagrees on the base of section {ndx}")
    # the statics are called through .text, in source order: align, initialize, morecore
    local = sorted(addr[".text"])
    names = ["align", "initialize", "morecore"]
    if len(local) != 3 or any(funcs[n][0] is not None for n in names):
        sys.exit(f"{version}: unexpected static functions {[hex(x) for x in local]}")
    for a, n in zip(local, names):
        out.append((a, n, "func", funcs[n][1]))
    for n, (val, size) in funcs.items():
        if val is not None:
            out.append((VRAMS[version] + val, n, "func", size))
    for n, (val, size, ndx) in objs.items():
        out.append((base[ndx] + val, n, "data", size))
    # the two static variables, pagesize and heapsize, follow the last hook in .bss
    bss = base["6"]
    statics = sorted(a for a in addr.get(".bss", ()) if a >= bss + 0x9C)
    if statics != [bss + 0x9C, bss + 0xA0]:
        sys.exit(f"{version}: unexpected .bss statics {[hex(x) for x in statics]}")
    out.append((bss + 0x9C, "pagesize", "data", 4))
    out.append((bss + 0xA0, "heapsize", "data", 4))
    return sorted(out)


def main():
    args = sys.argv[1:]
    write = "--write" in args
    versions = [a for a in args if a in VRAMS] or list(VRAMS)
    obj = build()
    text, rels = text_and_relocs(obj)
    if len(text) != TEXT_LEN:
        sys.exit(f"text is {len(text):#x} bytes, expected {TEXT_LEN:#x}")
    ok = True
    for v in versions:
        addr = check(v, text, rels)
        if addr is None:
            ok = False
            continue
        syms = symbols(v, obj, addr)
        if write:
            path = os.path.join(ROOT, f"symbol_addrs.libmalloc.{v}.txt")
            with open(path, "w") as f:
                f.write("// GNU malloc (gmalloc.c, 1995), generated by tools/libmalloc_check.py: do not edit.\n")
                f.write(f"// Compiled -g -mips1 with IDO 5.3 it matches ROM 0x{rom_off(v):X}-0x{rom_off(v) + TEXT_LEN:X} exactly.\n")
                for a, n, kind, size in syms:
                    t = "func" if kind == "func" else "u32"
                    f.write(f"{n} = 0x{a:08X}; // type:{t} size:0x{size:X} segment:main_code\n")
            print(f"wrote {path}")
    sys.exit(0 if ok else 1)


if __name__ == "__main__":
    main()
