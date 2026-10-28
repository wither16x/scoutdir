# scoutdir
A free and open-source web directory bruteforcer.

## Build instructions
1. Clone the repository
```sh
git clone https://github.com/wither16x/scoutdir
```
2. Make sure the following dependencies are installed on your system:
* `make`
* `libcurl`
* A C++23 compiler like `g++` or `clang++`
3. Run
```sh
make
```
If something went wrong and you want to rebuild, it is recommended to run
```sh
make clean
```
before running the Makefile again.
If no error happened, an executable should be located at `build/bin/scoutdir`.

## Installation
[Build the source code](#build-instructions) before.
Run
```sh
sudo make install
```
Root permissions are required because the program will be installed in `/usr/bin/`.

## Usage
Type `scoutdir -h` in your terminal to get a list of available options.