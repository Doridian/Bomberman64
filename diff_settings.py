"""asm-differ settings: tools/asm-differ/diff.py -mw <function>

The images are the code image (assets/code.bin, written by `make extract`)
and the rebuilt one; the map gives each function's place in them.  The
version is the one asm/ is extracted for (.version).
"""
from pathlib import Path


def apply(config, args):
    version_file = Path(__file__).resolve().parent / ".version"
    version = version_file.read_text().strip() if version_file.exists() else "us"
    config["baseimg"] = "assets/code.bin"
    config["myimg"] = f"build/{version}/code.bin"
    config["mapfile"] = f"build/{version}/bm64.{version}.map"
    config["source_directories"] = ["src", "include"]
    config["make_command"] = ["make", f"VERSION={version}"]
    config["arch"] = "mips"
    config["objdump_executable"] = "mips-linux-gnu-objdump"
