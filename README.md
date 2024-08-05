# R136

[![CMake](https://github.com/rbergen/R136/actions/workflows/cmake.yml/badge.svg)](https://github.com/rbergen/R136/actions/workflows/cmake.yml)
[![MSBuild](https://github.com/rbergen/R136/actions/workflows/msbuild.yml/badge.svg)](https://github.com/rbergen/R136/actions/workflows/msbuild.yml)

This is a text adventure a friend and I created all the way back in 1998.

After initially developing the game in what must have been QuickBASIC, it seems that I ported it to the C language I was just getting comfortable with at the time.

The C version of the game was developed for MS-DOS using the Borland C++ IDE, including the proprietary functions it provided. This repository holds a Windows console conversion
of that version, developed in Visual Studio 2019 Community Edition. You will need to install the "Desktop development with C++" workload to be able to build it. The original 1998 BASIC and C sources are included in the repo for the purposes of preserving history and general entertainment.

With the original DOS console long gone, I've refactored the game to use [ncurses](https://invisible-island.net/ncurses/announce.html) on \*nix-like systems, and [PDCurses](https://pdcurses.org/) on Windows. This enables some basic console manipulation, whilst not resorting to Windows-specific console functions. (Originally I used my own [PDCurses-sources-turned-Visual-Studio-project](https://github.com/rbergen/PDCurses) version of PDCurses, but I have since then switched to the PDCurses package supplied by the excellent [vcpkg tool](https://github.com/microsoft/vcpkg).)

After that, for non-Windows platforms, I've added a CMake build configuration. With this, R136 has been verified to build and run on at least:

* Windows using Visual Studio 2019, both as a VC++ solution and using CMake
* Windows with MSYS2/MinGW64 using GCC and PDCurses
* Windows with MSYS2/MinGW64 using GCC and ncurses
* WSL (Ubuntu) using GCC and ncurses
* MacOS using (MacOS native) Clang and ncurses

The game was originally only available in the Dutch language, but has now been translated to English as a second language. The source code itself is now fully in English, also. I guess international awareness & orientation took a couple of decades to develop in me, but here we are. (Note: getting R136 to start in English requires the `-e` command line argument to be passed to it; Dutch is still the default.)

## Credits

* Peter Wouda - co-creator, primary game designer and idea fountain extraordinaire. Since then, Peter became the creator of the physical board game [Skipp](https://www.skipp.game/en)
* Machiel Keizer - tester

## Building

Due to the fact that a CMake build configuration is included, you should be able to build R136 from source code on all systems that have installed:

* CMake version of 3.15 or newer
* a C/C++ build toolchain that is supported by CMake (which includes all "common" ones)
* a version of (n/PD)curses with wide-character support

On Windows, I recommend using the PDCurses version provided by vcpkg. Installation instructions for vcpkg can be found [on Microsoft's website](https://docs.microsoft.com/en-us/cpp/build/vcpkg).

## Other versions of R136

Also available are:

* A version of R136 developed in C#.NET, that includes both a console and a WebAssembly in-browser web application version. You can find that in the [R136.NET](https://github.com/rbergen/R136.NET) repository.
* An _updated_ version of the original 1998 procedural C++ version that requires Borland C++ 5.02 to build, and using that can be compiled to work on the original Intel 8086 CPU. That can be found in the [R136-8086](https://github.com/rbergen/R136-8086) repo.

_- Rutger van Bergen - [github.com/rbergen](https://github.com/rbergen)_
