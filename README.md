# DavidL's SG13 Miscellany

This is where I keep miscellaneous bits of code related to ISO C++ SG13 work.  Almost all of it compiles down to HTML5 + JavaScript code.

## Getting Started

To run a pre-built copy, only a web browser is needed, one with support for HTML5 Canvas + JavaScript.

To build, you'll need reasonably up-to-date copies of:
* [GNU Make](https://www.gnu.org/software/make/)
* [Emscripten](http://emscripten.org/)

With make and Emscripten installed, the following should be sufficient to build these demos:

```
git clone --recursive https://github.com/DavidLudwig/sg13-research
cd sg13-research
make
```

### MacOS prerequisite notes

In terms of prerequisities:
* GNU Make can be found in Xcode's Command Line Tools.  This is typically installed after running Xcode for the first time.  It can also be installed by running the following (after installing Xcode):

```xcode-select --install```

* Emscripten can be installed via [HomeBrew](https://brew.sh) (among other means), using the following command:

```brew install emscripten```


## Built With

* [SDL2](https://libsdl.org) - platform abstraction layer for graphics, user-input, and more
* [Emscripten](https://emscripten.org) - compiles C++ code to Javascript
* [Cairo](https://www.cairographics.org/) - 2D canvas library
