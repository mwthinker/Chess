Chess
======
A project aiming to simulate ai:s playing chess.

Building
======
CMake must be installed with at least version 2.8. Create a directory named "build" in the project directory.
Make sure a native compiler are installed.

<b> Unix </b>
Open a terminal inside the "build" directory and run:

$ cmake ..
$ make

The first to generate the makefile and the second to compile the Chess project.

$ ./Chess

to run the executable.

<b> Windows </b>
Run CMake (cmake-gui). Choose "Browse Source.." and point to the project folder.
Do the same for "Browse Build..." but point to the build folder.
Push the configure button and choose at least "Visual Studio 11" and push finish.
Push "Generate" then the visual studio solution will appear in the build folder.

This file is written by MwThinker.
