#!/usr/bin/env bash
set -euo pipefail

for tool in curl g++ clang++; do
    command -v "$tool" >/dev/null || {
        echo "$tool is required; run this project in its Dev Container" >&2
        exit 1
    }
done

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
