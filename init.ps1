$ErrorActionPreference = "Stop"
Set-StrictMode -Version Latest

$compiler = $null
$versionLine = $null
$clangMajor = 0
foreach ($candidate in (Get-Command clang++.exe, clang++-*.exe -All -ErrorAction SilentlyContinue)) {
    $candidateVersionLine = (& $candidate.Source --version 2>$null | Select-Object -First 1)
    if ($candidateVersionLine -match "version\s+(\d+)(?:\.\d+)*") {
        $candidateMajor = [int]$Matches[1]
        if ($candidateMajor -ge 18 -and $candidateMajor -gt $clangMajor) {
            $compiler = $candidate.Source
            $versionLine = $candidateVersionLine
            $clangMajor = $candidateMajor
        }
    }
}

if (-not $compiler) {
    throw "clang++ 18 or newer is required (see doc/WINDOWS_SETUP.md)"
}

$moduleSources = [IO.Path]::GetFullPath(
    (Join-Path (Split-Path $compiler) "..\share\libc++\v1")
)
foreach ($name in "std.cppm", "std.compat.cppm") {
    if (-not (Test-Path (Join-Path $moduleSources $name))) {
        throw "libc++ module source $name is missing; install mingw-mstorsjo-llvm-ucrt with Scoop"
    }
}

Write-Host "Detected toolchain:"
Write-Host "  $compiler"
Write-Host "  $versionLine"

New-Item -ItemType Directory -Force -Path "PPP", ".modules", ".clangd-include" | Out-Null
foreach ($name in "PPP.h", "PPPheaders.h", "PPP_support.h", "PPP.ixx") {
    Invoke-WebRequest -UseBasicParsing "https://www.stroustrup.com/$name" -OutFile "PPP/$name"
}

$supportPath = [IO.Path]::GetFullPath("PPP/PPP_support.h")
$support = [IO.File]::ReadAllText($supportPath)
$prefix = "#ifndef PPP_EXPORT`nimport std;`n#define PPP_EXPORT`n#endif`n"
$support = $prefix + $support.Replace("operator[](size_t", "operator[](std::size_t")
$utf8NoBom = New-Object System.Text.UTF8Encoding
[IO.File]::WriteAllText($supportPath, $support, $utf8NoBom)

function Invoke-Compiler([string[]]$Arguments) {
    & $compiler @Arguments
    if ($LASTEXITCODE -ne 0) {
        throw "clang++ failed with exit code $LASTEXITCODE"
    }
}

Invoke-Compiler -Arguments @(
    "-std=c++23", "-stdlib=libc++", "-I$moduleSources",
    "-Wno-reserved-module-identifier", "-x", "c++-module", "-c",
    (Join-Path $moduleSources "std.cppm"),
    "-fmodule-output=.modules/std.pcm", "-o", ".modules/std.obj"
)
Invoke-Compiler -Arguments @(
    "-std=c++23", "-stdlib=libc++", "-I$moduleSources",
    "-Wno-reserved-module-identifier", "-x", "c++-module", "-c",
    (Join-Path $moduleSources "std.compat.cppm"),
    "-fprebuilt-module-path=.modules",
    "-fmodule-output=.modules/std.compat.pcm", "-o", ".modules/std.compat.obj"
)
Invoke-Compiler -Arguments @(
    "-std=c++23", "-stdlib=libc++", "-x", "c++-module", "-c",
    "PPP/PPP.ixx", "-fprebuilt-module-path=.modules",
    "-fmodule-output=.modules/PPP.pcm", "-o", ".modules/PPP.obj"
)

$utf8Bom = New-Object -TypeName System.Text.UTF8Encoding -ArgumentList $true
[IO.File]::WriteAllText(
    [IO.Path]::GetFullPath(".modules/compiler.path"),
    "$compiler`n",
    $utf8Bom
)

Write-Host "Built std, std.compat, and PPP modules in .modules"
