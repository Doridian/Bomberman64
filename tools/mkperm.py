#!/usr/bin/env python3
"""Whole-file permuter setup for an -O3 object (or any all-C object):

    tools/mkperm.py FILE.c FUNC IMAGE_OFFSET OUTDIR [-O3] [-mips2]

base.c is FILE.c preprocessed (every function kept, so -O3's inlining and
cross-function register allocation happen as in the real build); target.o
is base.c compiled, with its .text replaced by the original bytes at
IMAGE_OFFSET (so only the functions that don't match yet differ, and the
relocations are ours).  The permuter then randomizes FUNC only and scores
the whole object.  Run:
    nice -n 10 .env/bin/python3 tools/decomp-permuter/permuter.py -j3 OUTDIR
"""
import os, subprocess, sys
W = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
VERSION = open(os.path.join(W, ".version")).read().strip()
cfile, func, off, out = sys.argv[1:5]
opt = next((a for a in sys.argv[5:] if a.startswith("-O") or a == "-g"), "-O3")
isa = next((a for a in sys.argv[5:] if a.startswith("-mips")), "-mips1")
off = int(off, 16)
os.makedirs(out, exist_ok=True)
out = os.path.abspath(out)
tmp = os.path.join(out, "tmp")
os.makedirs(tmp, exist_ok=True)
cc = (f"{W}/tools/ido/5.3/cc -c -G 0 -Xfullwarn -Xcpluscomm -nostdinc -non_shared -Wab,-r4300_mul "
      f"-D_LANGUAGE_C -D_FINALROM -DVERSION_{VERSION.upper()} -woff 649,838,712,807 -I {W}/include -I {W}/include/PR "
      f"{opt} {isa} -32")
# preprocess (keep it C89-ish for pycparser: drop line markers)
pp = subprocess.run(["cpp", "-P", "-undef", "-D_LANGUAGE_C", "-D_FINALROM", f"-DVERSION_{VERSION.upper()}", "-D__sgi",
                     "-I", f"{W}/include", "-I", f"{W}/include/PR", cfile],
                    capture_output=True, text=True, check=True).stdout
import re as _re
# The permuter turns every function but the target into a declaration
# unless it's `inline`, and drops `static` from function declarations: so
# mark the other definitions `inline` and every `static` function
# `_Noreturn`, and compile.sh turns them back.
lines = pp.split("\n")
for k, l in enumerate(lines):
    if _re.match(r"^static\s", l) and "(" in l:
        l = "_Noreturn " + l[len("static "):]
    m = _re.match(r"^(_Noreturn )?([A-Za-z_][\w \*]*?)\b(func_\w+)\s*\(.*\)\s*\{?\s*$", l)
    if m and not l.rstrip().endswith(";") and m.group(3) != func:
        l = "inline " + l
    lines[k] = l
pp = "\n".join(lines)
open(os.path.join(out, "base.c"), "w").write(pp)
with open(os.path.join(out, "compile.sh"), "w") as f:
    f.write(f'#!/usr/bin/env bash\nset -euo pipefail\nINPUT="$(realpath "$1")"\nOUTPUT="$(realpath "$3")"\n'
            f'cd {tmp}\nT=$(mktemp {tmp}/XXXXXX.c)\n'
            f'sed -e "s/\\b_Noreturn\\b/static/g" -e "s/\\binline //g" "$INPUT" > "$T"\n'
            f'{cc} "$T" -o "$OUTPUT"\nrm -f "$T"\n')
os.chmod(os.path.join(out, "compile.sh"), 0o755)
subprocess.run([os.path.join(out, "compile.sh"), os.path.join(out, "base.c"), "-o",
                os.path.join(out, "base.o")], check=True)
subprocess.run(["mips-linux-gnu-objcopy", "-O", "binary", "-j", ".text", os.path.join(out, "base.o"),
                os.path.join(tmp, "t.bin")], check=True)
n = os.path.getsize(os.path.join(tmp, "t.bin"))
code = bytearray(open(f"{W}/assets/code.bin", "rb").read()[off:off + n])
mine = open(os.path.join(tmp, "t.bin"), "rb").read()
# relocated words keep our relocated bits (the addend IDO wrote), so that
# only real differences count
import re
rel = subprocess.run(["mips-linux-gnu-readelf", "-rW", os.path.join(out, "base.o")],
                     capture_output=True, text=True).stdout
sec = None
for line in rel.splitlines():
    m = re.match(r"Relocation section '\.rel\.?(\S*)'", line)
    if m:
        sec = m.group(1); continue
    m = re.match(r"^([0-9a-f]{8})\s+\S+\s+(\S+)", line)
    if m and sec == "text":
        o = int(m.group(1), 16)
        mask = 0x03FFFFFF if m.group(2) == "R_MIPS_26" else 0xFFFF
        w = int.from_bytes(code[o:o + 4], "big") & ~mask | int.from_bytes(mine[o:o + 4], "big") & mask
        code[o:o + 4] = w.to_bytes(4, "big")
open(os.path.join(tmp, "orig.bin"), "wb").write(code)
# patch the bytes in place (objcopy --update-section drops the relocations)
hdr = subprocess.run(["mips-linux-gnu-readelf", "-SW", os.path.join(out, "base.o")],
                     capture_output=True, text=True).stdout
m = re.search(r"\]\s+\.text\s+\S+\s+[0-9a-f]+\s+([0-9a-f]+)\s+([0-9a-f]+)", hdr)
foff = int(m.group(1), 16)
obj = bytearray(open(os.path.join(out, "base.o"), "rb").read())
obj[foff:foff + n] = code
open(os.path.join(out, "target.o"), "wb").write(obj)
open(os.path.join(out, "settings.toml"), "w").write(f'func_name = "{func}"\ncompiler_type = "ido"\n')
print(out)
