#!/usr/bin/env bash
# First-draft C for one function:  tools/m2c.sh <function> [m2c args]
#
# Finds the function's .s under asm/nonmatchings/ (it must be GLOBAL_ASM in
# a C file, so that splat wrote it there; tools/c_stub.py starts one) and
# runs m2c on it with the project venv.  The function's object's other .s
# files go along as context (--context is for a C header), so that calls
# to and jumps into its neighbours resolve.  Pass m2c's own flags after the
# name: --valid-syntax, --globals=none, --context include/common.h, ...
set -euo pipefail
ROOT=$(cd "$(dirname "$0")/.." && pwd)
FN=${1:?usage: $0 <function> [m2c args]}
shift
ASM=$(find "$ROOT/asm/nonmatchings" -name "$FN.s" 2>/dev/null | head -1)
if [ -z "$ASM" ]; then
    echo "no $FN.s under asm/nonmatchings (not GLOBAL_ASM in a C file, or not extracted)" >&2
    exit 1
fi
cd "$ROOT"
exec .env/bin/python3 tools/m2c/m2c.py --target mips-ido-c "$@" "$ASM"
