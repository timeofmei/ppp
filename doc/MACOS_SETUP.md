# macOS Setup (Native, No Docker)

This guide is for macOS users who do **not** want to use Docker. It sets up a native Homebrew toolchain for the PPP3e code in this repository.

The project needs **Clang 23+ and its matching libc++** to provide and compile the `std` / `std.compat` modules (and include `clangd` for IDE support).

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

Verify the toolchain:

```bash
"$(brew --prefix llvm)/bin/clang++" --version  # clang version 23 or newer
```

## 4. Build the modules

Clone and open this repository, then run:

```bash
./init.sh
```

`init.sh` downloads the PPP headers and compiles `std`, `std.compat`, and `PPP` into `.modules`.

> [!TIP]
> After Homebrew upgrades LLVM, rerun `./init.sh`; it rebuilds the modules and records the compiler used by the VS Code build task.

## 5. Compile and run a program

```bash
PPP_CXX=$(<.modules/compiler.path)
"$PPP_CXX" -std=c++23 -stdlib=libc++ \
    -IPPP -fprebuilt-module-path=.modules \
    c1/hello.cpp .modules/std.o .modules/PPP.o -o c1/hello.out
./c1/hello.out
```
