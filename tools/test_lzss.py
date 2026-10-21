#!/usr/bin/env python3
"""Self-test for tools/hudson_lzss.py that needs no ROM (CI runs it): the
codec round-trips, and the C and Python encoders give identical streams.
The ROM check (exact recompression of Hudson's data) is lzss_check.py.

  test_lzss.py [--no-c]
"""
import argparse
import random
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import hudson_lzss  # noqa: E402


def samples():
    rng = random.Random(64)
    yield b""
    yield b"\0"
    yield b"\0" * 5000                       # matches into the zero window
    yield bytes(range(256)) * 9
    yield bytes(rng.randrange(256) for _ in range(3000))
    for _ in range(20):                      # repetitive, like code and tiles
        alphabet = bytes(rng.randrange(256) for _ in range(rng.randint(1, 12)))
        yield bytes(rng.choice(alphabet) for _ in range(rng.randint(1, 6000)))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--no-c", action="store_true", help="Python encoder only")
    a = ap.parse_args()
    have_c = hudson_lzss._load_c() is not None
    if not a.no_c and not have_c:
        sys.exit("C encoder not built (make build/tools/libhudson_lzss.so), or pass --no-c")
    n = 0
    for data in samples():
        py = hudson_lzss.encode(data, force_py=True)
        got, used = hudson_lzss.decode(py)
        assert got == data and used == len(py), f"round trip, {len(data)} bytes"
        if not a.no_c:
            assert hudson_lzss.encode(data) == py, f"C != Python, {len(data)} bytes"
        n += 1
    print(f"{n} samples round-trip{'' if a.no_c else ', C and Python agree'}")


if __name__ == "__main__":
    main()
