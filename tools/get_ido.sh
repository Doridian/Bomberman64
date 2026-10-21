#!/usr/bin/env bash
# Fetch decompals' static recompilation of IDO 5.3 (the compiler Bomberman 64
# was built with) into tools/ido/5.3, checked against pinned sha256s.
#
#   tools/get_ido.sh
set -euo pipefail
VER=v1.2
DEST=$(dirname "$0")/ido/5.3
[ -x "$DEST/cc" ] && exit 0

case "$(uname -s)-$(uname -m)" in
    Linux-x86_64)  OS=linux;     SUM=ab5c741561f80913d58c8b074771f23941a3edd312505a8ebed6d1dfeb65e506 ;;
    Linux-aarch64) OS=linux-arm; SUM=b6844c986fa65d7de4ce10b27583769a5ec7a88ae37a151f6dc66c929d3e1c92 ;;
    Darwin-*)      OS=macos;     SUM=5b1ca006ee4b158ffba0422fc3f00b9b330f9036f279bae2ea1b4703317ad9c0 ;;
    *) echo "no IDO recomp build for $(uname -s)-$(uname -m)" >&2; exit 1 ;;
esac

TMP=$(mktemp)
trap 'rm -f "$TMP"' EXIT
curl -fsSL -o "$TMP" "https://github.com/decompals/ido-static-recomp/releases/download/$VER/ido-5.3-recomp-$OS.tar.gz"
echo "$SUM  $TMP" | sha256sum --check --quiet
mkdir -p "$DEST"
tar xzf "$TMP" -C "$DEST"
echo "IDO 5.3 ($VER, $OS) in $DEST"
