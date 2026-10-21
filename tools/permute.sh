#!/usr/bin/env bash
# Set up a decomp-permuter directory for one function:
#
#   tools/permute.sh <function> [draft.c] [-- import.py args]
#
# base.c is the function's C file with the function's GLOBAL_ASM line
# replaced by the draft (a file holding the function's definition, plus any
# declarations it needs), or without one by m2c's output (tools/m2c.sh).
# The other GLOBAL_ASM lines are dropped: the permuter compiles this
# function only.  target.o is the function's .s assembled on its own, so
# the function must still be GLOBAL_ASM (splat writes no .s for C
# functions).  compile.sh is the command make would use for the file (IDO,
# the Makefile's flags and the file's overrides such as -O3 or -g).
#
# The directory is permuter/nonmatchings/<function>[-N]/; the script prints
# it.  Then, from the repo root:
#
#   .env/bin/python3 tools/decomp-permuter/permuter.py -j16 permuter/nonmatchings/<function>
#
# The version is the one asm/ is extracted for (.version).
set -euo pipefail
ROOT=$(cd "$(dirname "$0")/.." && pwd)
usage="usage: $0 <function> [draft.c] [-- import.py args]"
FN=${1:?$usage}
shift
DRAFT=
if [ $# -gt 0 ] && [ "$1" != "--" ]; then DRAFT=$(realpath "$1"); shift; fi
[ "${1:-}" = "--" ] && shift
VERSION=$(cat "$ROOT/.version" 2>/dev/null || echo us)
PY=$ROOT/.env/bin/python3
PERMUTER=$ROOT/tools/decomp-permuter
OUT=$ROOT/permuter

ASM=$(find "$ROOT/asm/nonmatchings" -name "$FN.s" 2>/dev/null | head -1 || true)
[ -n "$ASM" ] || { echo "no $FN.s under asm/nonmatchings (not GLOBAL_ASM, or not extracted)" >&2; exit 1; }
OBJ=${ASM#"$ROOT/asm/nonmatchings/"}
OBJ=$(dirname "$OBJ")
CFILE=src/$OBJ.c
[ -f "$ROOT/$CFILE" ] || { echo "no $CFILE" >&2; exit 1; }

# The compile command make would run for this file, without asm-processor
# (PERMUTER=1 selects the plain recipe); the per-file flags come with it.
# Paths are made absolute, so that compile.sh can run anywhere.
CC_LINE=$(cd "$ROOT" && make -n -B VERSION="$VERSION" PERMUTER=1 "build/$VERSION/$CFILE.o" |
          grep -m1 '^tools/ido/5\.3/cc ')
COMPILER=$("$PY" - "$CC_LINE" "$CFILE" "$ROOT" <<'PYEOF'
import os, shlex, sys
line, cfile, root = sys.argv[1:]
out = []
parts = iter(shlex.split(line))
for p in parts:
    if p in ("-o", "-I"):
        arg = next(parts)
        if p == "-I":
            out += ["-I", os.path.normpath(os.path.join(root, arg))]
        continue
    if p == cfile:
        continue
    if p.startswith("tools/"):
        p = os.path.join(root, p)
    out.append(p)
print(shlex.join(out))
PYEOF
)

WORK=$ROOT/build/permuter
mkdir -p "$WORK" "$OUT"

BODY=$WORK/$FN.draft.c
if [ -n "$DRAFT" ]; then
    cp "$DRAFT" "$BODY"
else
    "$ROOT/tools/m2c.sh" "$FN" > "$BODY"
fi
TMPC=$WORK/$FN.c
"$PY" - "$ROOT/$CFILE" "$BODY" "$FN" "$TMPC" <<'PYEOF'
import re, sys
src, body, fn, out = sys.argv[1:]
body = open(body).read()
lines = []
for line in open(src).read().splitlines(keepends=True):
    m = re.match(r'\s*#pragma\s+GLOBAL_ASM\("([^"]*)"\)', line)
    if m:
        if m.group(1).endswith("/" + fn + ".s"):
            lines.append(body if body.endswith("\n") else body + "\n")
        continue
    lines.append(line)
open(out, "w").write("".join(lines))
PYEOF

# The target: the function's .s alone (import.py adds the permuter's
# prelude, with glabel and nonmatching, and the float register names).
TMPS=$WORK/$FN.s
cp "$ASM" "$TMPS"

SETTINGS=$WORK/$FN.toml
cat > "$SETTINGS" <<EOF
compiler_type = "ido"
compiler_command = $("$PY" -c 'import json,sys; print(json.dumps(sys.argv[1]))' "$COMPILER")
assembler_command = "mips-linux-gnu-as -EB -march=vr4300 -mabi=32"
EOF

cd "$OUT"
LOG=$WORK/$FN.import.log
"$PY" "$PERMUTER/import.py" --settings "$SETTINGS" "$TMPC" "$TMPS" "$@" 2>&1 | tee "$LOG"
DIR=$(sed -n 's/^Done. Imported into //p' "$LOG")
[ -n "$DIR" ] || exit 1
DIR=$OUT/$DIR

# IDO leaves its temporaries in the working directory when the permuter
# kills a compile, so compile in a directory of its own.
mkdir -p "$DIR/tmp"
sed -i "s|^cd .*|cd $(printf '%q' "$DIR/tmp")|" "$DIR/compile.sh"
"$DIR/compile.sh" "$DIR/base.c" -o "$DIR/base.o" >/dev/null 2>&1 ||
    echo "warning: base.c does not compile; check it with $DIR/compile.sh" >&2
echo "permuter directory: ${DIR#"$ROOT"/}"
