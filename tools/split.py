#!/usr/bin/env python3
"""Run splat on a version's config, reading the C files' names as that
version's.

  split.py <version>          splat split bm64.<version>.yaml

The C uses us's names in every version (tools/vermap.py), but splat names
eu's and jp's functions and data by their own addresses; `vermap.py
--rename` gives them us's names only after splat.  splat, though, reads
each C file (a `c` subsegment) for the functions it defines and its
GLOBAL_ASM lines, and writes asm/nonmatchings/<object>/<function>.s for
each GLOBAL_ASM function it finds by its own name.  So outside us the names
it reads from a C file are first turned into the ones it gives
(vermap.version_name(): `func_80296B3C` is func_<jp address of the same
function>, `func_X_jp` is jp's X, a us-only function `func_X_us`, which
nothing is called), and the rename then gives the .s files and their names
us's names back.  In us this is plain splat.
"""
import runpy
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))


def main():
    version = sys.argv[1]
    if version != "us":
        import vermap
        from splat.segtypes.common.c import CommonSegC
        vm = vermap.read_map(vermap.map_file(version))

        def translated(fn):
            return staticmethod(lambda path: {vermap.version_name(vm, version, n) for n in fn(path)})
        for attr in ("get_funcs_defined_in_c", "get_global_asm_funcs", "get_global_asm_rodata_syms"):
            setattr(CommonSegC, attr, translated(getattr(CommonSegC, attr)))
    sys.argv = ["splat", "split", f"bm64.{version}.yaml"]  # make runs in the root
    runpy.run_module("splat", run_name="__main__", alter_sys=True)


if __name__ == "__main__":
    main()
