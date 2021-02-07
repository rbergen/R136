# R136

This is text adventure a friend and I created all the way back in 1998.

After initially developing the game in what must have been QuickBASIC, it seems that I ported it to the C language I was just getting comfortable with at the time.

The C version of the game was developed for MS-DOS using the Borland C++ IDE, including the proprietary functions it provided. This repository holds a Windows console conversion 
of that version, developed in Visual Studio 2019 Community Edition. You will need to install the "Desktop development with C++" workload to be able to build it. The original 1998 
BASIC and C sources are included in the repo for the purposes of preserving history and general entertainment.

With the original DOS console long gone, I've refactored the game to use a [PDCurses-sources-turned-Visual-Studio-project](https://github.com/rbergen/PDCurses) I created more or less accidentally. This enables some basic console manipulation, whilst not resorting to Windows-specific console functions. 

After that, for non-Windows platforms, I've added a CMake build configuration. With this, R136 has been verified to build and run on at least:
* Windows using Visual Studio 2019
* Windows with MSYS2/MinGW64 using GCC and PDCurses
* MacOS using (MacOS native) CLang and ncurses

Oh, yeah, the game is in Dutch. I guess international awareness & orientation is something that developed in me over the past couple of decades...

## Credits

* Peter Wouda - co-creator, primary game designer and idea fountain extraordinaire. Since then, Peter became the creator of the physical board game [Skipp](https://www.skipp.game/en)
* Machiel Keizer - tester
* Authors of source code used within this C(++) port, as indicated in respective source files.
