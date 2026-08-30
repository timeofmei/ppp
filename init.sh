#!/usr/bin/env bash
set -euo pipefail

for tool in curl g++ clang++; do
    command -v "$tool" >/dev/null || {
        echo "$tool is required (see README)" >&2
        exit 1
    }
done

# Detect toolchain versions (README: requires GCC 15+ and Clang 21+)
gpp_version=$(g++ --version 2>/dev/null | head -n1 | grep -oE '[0-9]+(\.[0-9]+)*' | head -n1 || true)
clang_version=$(clang++ --version 2>/dev/null | head -n1 | grep -oE '[0-9]+(\.[0-9]+)*' | head -n1 || true)

# version_ge A B: succeeds if A >= B (dotted version strings)
version_ge() {
    [ "$(printf '%s\n%s\n' "$2" "$1" | sort -V | head -n1)" = "$2" ]
}

check_min_version() {
    local pretty="$1" version="$2" min="$3"
    if [ -z "$version" ]; then
        echo "Could not determine $pretty version" >&2
        return 1
    fi
    if ! version_ge "$version" "$min"; then
        echo "$pretty $version is too old; PPP requires $pretty $min or newer (see README)" >&2
        return 1
    fi
    echo "  $pretty $version (requires $pretty $min+)"
}

echo "Detected toolchain:"
check_min_version "g++" "$gpp_version" 15
check_min_version "clang++" "$clang_version" 21

mkdir -p PPP

curl -fL https://www.stroustrup.com/PPP.h -o PPP/PPP.h
curl -fL https://www.stroustrup.com/PPP_support.h -o PPP/PPP_support.h
curl -fL https://www.stroustrup.com/PPP.ixx -o PPP/PPP.ixx
sed -i 's/operator\[\](size_t/operator[](std::size_t/g' PPP/PPP_support.h

mkdir -p .modules

modules_json=$(g++ -print-file-name=libstdc++.modules.json)
if [ ! -f "$modules_json" ]; then
    echo "libstdc++ standard modules require GCC 15 or newer; rebuild the Dev Container" >&2
    exit 1
fi

std_source=$(awk -F'"' '$4 ~ /\/std\.cc$/ { print $4; exit }' "$modules_json")
std_compat_source=$(awk -F'"' '$4 ~ /\/std\.compat\.cc$/ { print $4; exit }' "$modules_json")

clang++ -std=c++23 -x c++-module -c "$std_source" -Wno-reserved-module-identifier -fmodule-output=.modules/std.pcm -o .modules/std.o
clang++ -std=c++23 -x c++-module -c "$std_compat_source" -Wno-reserved-module-identifier -fprebuilt-module-path=.modules -fmodule-output=.modules/std.compat.pcm -o .modules/std.compat.o
clang++ -std=c++23 -x c++-module -c PPP/PPP.ixx -fprebuilt-module-path=.modules -fmodule-output=.modules/PPP.pcm -o .modules/PPP.o
