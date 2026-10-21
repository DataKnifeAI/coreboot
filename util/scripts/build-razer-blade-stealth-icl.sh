#!/usr/bin/env bash
# Build a stitched 16 MiB coreboot image for Razer Blade Stealth ICL (LY320).
# Requires local blobs (never committed):
#   3rdparty/blobs/mainboard/razer/blade_stealth_icl/{descriptor,me}.bin
#   3rdparty/fsp/IceLakeFspBinPkg/Fsp.fd
#   3rdparty/intel-microcode/intel-ucode/06-7e-05
# Does not run flashrom.
set -euo pipefail
ROOT="$(cd "$(dirname "$0")/../.." && pwd)"
cd "$ROOT"

need() { [[ -f "$1" ]] || { echo "missing: $1" >&2; exit 1; }; }
need 3rdparty/blobs/mainboard/razer/blade_stealth_icl/descriptor.bin
need 3rdparty/blobs/mainboard/razer/blade_stealth_icl/me.bin
need 3rdparty/fsp/IceLakeFspBinPkg/Fsp.fd
need 3rdparty/intel-microcode/intel-ucode/06-7e-05

export PATH="${ROOT}/util/crossgcc/xgcc/bin:${PATH}"
make defconfig KBUILD_DEFCONFIG=configs/config.razer_blade_stealth_icl
make -j"$(nproc)"
make -C util/ifdtool

echo
echo "=== image ==="
ls -la build/coreboot.rom
sha256sum build/coreboot.rom
echo
echo "=== ifdtool -d ==="
./util/ifdtool/ifdtool -d build/coreboot.rom || true
echo
echo "=== ifdtool -t ==="
./util/ifdtool/ifdtool -t build/coreboot.rom || true
echo
echo "=== cbfstool print ==="
./build/cbfstool build/coreboot.rom print
echo
echo "DONE — do not flashrom -w without PREFLASH signoff."
