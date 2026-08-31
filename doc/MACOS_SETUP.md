# macOS Setup (Native, No Docker)

This guide is for macOS users who do **not** want to use Docker. It sets up a native Homebrew toolchain for the PPP3e code in this repository.

The project needs:

- **GCC 15+** — provides `libstdc++.modules.json`, the source of the `std` / `std.compat` C++ standard library modules.
- **Clang 21+** — compiles those modules into `.pcm` / `.o` files (and `clangd` for IDE support).
- **GNU sed + curl + bash** — `init.sh` uses a GNU `sed -i` form that macOS's BSD `sed` does not support.

> [!WARNING]
> Apple's own Clang (from Xcode Command Line Tools) is **too old** for this project (it tracks roughly LLVM 16/17), and macOS ships **no GCC at all**. You must install both from Homebrew.

> [!NOTE]
> **Why libstdc++ and not libc++?** macOS could drop GCC entirely by building the `std` module from Homebrew's bundled libc++ (only `brew install llvm` needed). We keep libstdc++ anyway so that macOS stays **identical to every other environment in this repo** (Linux/Docker and Windows/MSYS2): same standard library, same module artifacts, same compile flags, same behavior. Cross-platform consistency matters more than a slightly simpler macOS install.

## 1. Install Xcode Command Line Tools

Homebrew's Clang needs the Apple SDK:

```bash
xcode-select --install
```

## 2. Install Homebrew (if not already installed)

```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

## 3. Install the toolchain

```bash
brew install gcc llvm gnu-sed
```

- `gcc` → GCC 16 (≥ 15) — libstdc++ + `libstdc++.modules.json`.
- `llvm` → Clang 23 (≥ 21) — the module compiler; also provides `clangd`.
- `gnu-sed` → GNU `sed` with `-i` semantics. **Required** — without it, `init.sh` fails at the `sed -i` step because BSD `sed` has a different `-i` syntax.

## 4. Put the Homebrew tools first on `PATH`

Homebrew's `gcc` and `llvm` are "keg-only", so they are not linked into the default bin directory. Add them (and gnu-sed) ahead of Apple's tools. On Apple Silicon Homebrew lives in `/opt/homebrew`, on Intel in `/usr/local` — `$(brew --prefix)` handles both. Add to `~/.zshrc`:

```bash
export PATH="$(brew --prefix)/opt/gcc/bin:$(brew --prefix)/opt/llvm/bin:$(brew --prefix)/opt/gnu-sed/libexec/gnubin:$PATH"
```

> [!IMPORTANT]
> Without this, `g++`/`clang++` resolve to Apple's Clang, and `init.sh` fails both the version checks and the `libstdc++.modules.json` lookup.

Verify in a new terminal:

```bash
g++ --version      # Homebrew GCC 16.x
clang++ --version  # clang version 23.x
```

## 5. macOS-specific module build

Homebrew's Clang defaults to `libc++`, but this project's `std` module is built from GCC's `libstdc++`. Every `clang++` invocation therefore needs two extra flags:

```bash
-stdlib=libstdc++                                  # use libstdc++, not libc++
--gcc-install-dir="$(brew --prefix)/opt/gcc"       # let clang find Homebrew gcc's headers and libraries
```

`init.sh` detects macOS automatically and applies the two flags above itself, so just run it as usual:

```bash
./init.sh
```

> [!TIP]
> The current Homebrew versions (GCC 16 + Clang 23) are quite new. If compiling the `std` module hits odd standard-library errors, pin the exact versions used by the Dev Container with `brew install gcc@15 llvm@21` and adjust the `PATH` lines above accordingly.

## 6. Compile and run a program

Use the same two flags for every program:

```bash
clang++ -std=c++23 -stdlib=libstdc++ --gcc-install-dir="$(brew --prefix)/opt/gcc" \
    -IPPP -fprebuilt-module-path=.modules \
    c1/hello.cpp .modules/std.o .modules/PPP.o -o c1/hello.out
./c1/hello.out
```

> [!NOTE]
> If the linker reports that it cannot find libstdc++, add `-L"$(brew --prefix)/opt/gcc/lib/gcc/current" -lstdc++` to the link line.

## 7. Use it from VS Code

1. Install the **clangd** extension.
2. `clangd` comes from the `llvm` formula and picks up `compile_flags.txt` and `.clangd` automatically.

---

## Why this works (for reference)

The `std` and `std.compat` modules are compiled by Clang from the module sources that ship inside GCC's libstdc++ (`libstdc++.modules.json`). That is why **both** GCC 15+ and Clang 21+ are required: GCC supplies the standard-library module sources, Clang compiles them. `PPP.ixx` (`export module PPP; export import std;`) and `PPP.h` (`import PPP;`) build on top of those modules, so every example in `c1/` and `c2/` shares the same precompiled `.pcm` / `.o` files.
