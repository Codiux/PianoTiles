# PianoTiles
A simple piano tiles game

## Building
To build the source code, one needs to have these installed:
 - CMake
 - msvc / g++ / clang++

and these libraries must exist and be locatable:
 - [Bromeon/Thor](https://github.com/Bromeon/Thor)
 - [fmtlib/fmt](https://github.com/fmtlib/fmt)
 - [gabime/spdlog](https://github.com/gabime/spdlog)
 - [jbeder/yaml-cpp](https://github.com/jbeder/yaml-cpp)
 - [texus/tgui (0.9.x)](https://github.com/texus/tgui)
 - [SFML/SFML (2.5)](https://github.com/SFML/SFML/)

### Linux
Prerequisites:
 - make

To build it, type in these commands inside the terminal:
```
$ mkdir build
$ cd build
$ cmake ..
$ make .
```
Make sure you're on the repo's root directory at the start of executing those commands.

The executable "PianoTiles" should appear if the build processes succeeded.

### Windows
Work In Progress

### Dependencies
In order for the dependencies to be found, one must appends `CMAKE_PREFIX_PATH` with the directory in which `FindXXX.cmake`, `XXXConfig.cmake` or `xxx-config.cmake` can be found. SFML's SFMLConfig.cmake is usually located at `/usr/local/lib/cmake/SFML/` directory in linux systems, in which it's usually already included by default. If you can't find it, try using the `locate` command in linux, for example `locate SFMLConfig.cmake`.
