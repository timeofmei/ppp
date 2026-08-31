#!/usr/bin/env bash
set -euo pipefail


PPP_CXX=clang++
command -v clang++-23 >/dev/null && PPP_CXX=clang++-23

for tool in curl "$PPP_CXX"; do
    command -v "$tool" >/dev/null || {
        echo "$tool is required (see README)" >&2
        exit 1
    }
done

# Detect toolchain version (README: requires Clang 23+)
clang_version=$("$PPP_CXX" --version 2>/dev/null | head -n1 | grep -oE '[0-9]+(\.[0-9]+)*' | head -n1 || true)

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
check_min_version "$PPP_CXX" "$clang_version" 23

mkdir -p PPP

curl -fL https://www.stroustrup.com/PPP.h -o PPP/PPP.h
curl -fL https://www.stroustrup.com/PPP_support.h -o PPP/PPP_support.h
curl -fL https://www.stroustrup.com/PPP.ixx -o PPP/PPP.ixx
sed -i 's/operator\[\](size_t/operator[](std::size_t/g' PPP/PPP_support.h

mkdir -p .modules

modules_json="$("$PPP_CXX" -print-resource-dir)/../../libc++.modules.json"
if [ ! -f "$modules_json" ]; then
    echo "libc++ standard modules are missing; install the libc++ 23 development package" >&2
    exit 1
fi

modules_dir=$(dirname "$modules_json")
std_source=$(awk -F'"' '$4 ~ /\/std\.cppm$/ { print $4; exit }' "$modules_json")
std_compat_source=$(awk -F'"' '$4 ~ /\/std\.compat\.cppm$/ { print $4; exit }' "$modules_json")

case "$std_source" in /*) ;; *) std_source="$modules_dir/$std_source" ;; esac
case "$std_compat_source" in /*) ;; *) std_compat_source="$modules_dir/$std_compat_source" ;; esac
if [ ! -f "$std_source" ] || [ ! -f "$std_compat_source" ]; then
    echo "libc++ std/std.compat module sources are missing; reinstall the libc++ 23 development package" >&2
    exit 1
fi

"$PPP_CXX" -std=c++23 -stdlib=libc++ -x c++-module -c "$std_source" -Wno-reserved-module-identifier -fmodule-output=.modules/std.pcm -o .modules/std.o
"$PPP_CXX" -std=c++23 -stdlib=libc++ -x c++-module -c "$std_compat_source" -Wno-reserved-module-identifier -fprebuilt-module-path=.modules -fmodule-output=.modules/std.compat.pcm -o .modules/std.compat.o
"$PPP_CXX" -std=c++23 -stdlib=libc++ -x c++-module -c PPP/PPP.ixx -fprebuilt-module-path=.modules -fmodule-output=.modules/PPP.pcm -o .modules/PPP.o

# Install the workspace keybinding into VS Code's per-user keybindings.json.
# VS Code ignores workspace-level keybindings (.vscode/keybindings.json), so a
# tracked copy is placed where VS Code actually reads it (Dev Container / Remote only).
if [ -d "$HOME/.vscode-server" ]; then
    mkdir -p "$HOME/.vscode-server/data/User"
    cp .devcontainer/keybindings.json "$HOME/.vscode-server/data/User/keybindings.json"
    echo "Installed keybindings -> $HOME/.vscode-server/data/User/keybindings.json"
fi
