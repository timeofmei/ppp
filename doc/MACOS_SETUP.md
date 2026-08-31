# macOS Setup (Native, No Docker)

This guide is for macOS users who do **not** want to use Docker. It sets up a native Homebrew toolchain for the PPP3e code in this repository.

The project needs:

- **Clang 23+ and its matching libc++** — provide and compile the `std` / `std.compat` modules (and include `clangd` for IDE support).

> [!WARNING]
> Apple's own Clang (from Xcode Command Line Tools) is **too old** for this project (it tracks roughly LLVM 16/17). Install Homebrew LLVM instead.

> [!NOTE]
> Homebrew LLVM includes the compiler, standard library, and module sources in one formula.

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
brew install llvm
```

- `llvm` → the current Clang, matching libc++, and `clangd`.

## 4. Put the Homebrew tools first on `PATH`

Homebrew's `llvm` is "keg-only", so it is not linked into the default bin directory. Add it ahead of Apple's tools. On Apple Silicon Homebrew lives in `/opt/homebrew`, on Intel in `/usr/local` — `$(brew --prefix)` handles both. Add to `~/.zshrc`:

```bash
export PATH="$(brew --prefix)/opt/llvm/bin:$PATH"
```

> [!IMPORTANT]
> Without this, `clang++` resolves to Apple's Clang and `init.sh` fails the version check and libc++ module lookup.

Verify in a new terminal:

```bash
clang++ --version  # clang version 23 or newer
```

## 5. Build the modules

This project builds the standard library modules from Homebrew LLVM's libc++. `init.sh` selects it explicitly with:

```bash
-stdlib=libc++
```

`init.sh` applies this option itself, so just run it as usual:

```bash
./init.sh
```

> [!TIP]
> After Homebrew upgrades LLVM, rerun `./init.sh`; it rebuilds the modules and records the compiler used by the VS Code build task.

## 6. Compile and run a program

Use the same standard and library options for every program:

```bash
PPP_CXX=$(<.modules/compiler.path)
"$PPP_CXX" -std=c++23 -stdlib=libc++ \
    -IPPP -fprebuilt-module-path=.modules \
    c1/hello.cpp .modules/std.o .modules/PPP.o -o c1/hello.out
./c1/hello.out
```

## 7. Use it from VS Code

1. Install the **clangd** extension.
2. `clangd` comes from the `llvm` formula and picks up `compile_flags.txt` and `.clangd` automatically.

---

## Why this works (for reference)

The `std` and `std.compat` modules are compiled by Clang from the sources listed in libc++'s `libc++.modules.json`. `PPP.ixx` (`export module PPP; export import std;`) and `PPP.h` (`import PPP;`) build on top of those modules, so every example shares the same precompiled `.pcm` / `.o` files.
