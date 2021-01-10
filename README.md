# R136

This is text adventure a friend and I created all the way back in 1998.

After initially developing the game in what must have been QuickBASIC, I ported it to the C language I was just getting comfortable with at the time.

The C version of the game was developed for MS-DOS using the Borland C++ IDE, including the proprietary functions it provided. This repository holds a Windows console conversion 
of that version, developed in Visual Studio 2019 Community Edition. You will need to install the "Desktop development with C++" workload to be able to build it. The original 1998 BASIC and C sources are included in the repo for the purposes of preserving history and general entertainment.

A next step would be a refactor to a (n/pd)curses-based implementation, to remove the dependency on functions that are specific to the Windows console. As this would be somewhat 
of an undertaking, any outsider encouragement to perform this step would probably make a big difference towards my motivation to actually do it. :)

Oh, yeah, the game is in Dutch. I guess international awareness & orientation is something that developed in me over the past couple of decades...

## Credits

* Peter Wouda - co-creator, primary game designer and idea fountain extraordinaire. Since then, Peter became the creator of the physical board game [Skipp](https://www.skipp.game/en)
* Machiel Keizer - tester
