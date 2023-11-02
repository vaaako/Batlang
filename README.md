# Batlang 🦇

Batlang is my Hobby Programming language, making just for learning and fun. It is called Batlang because bat 🦇 is my favorite animal and BAT is in use alredy

>Batlang has no relation with BAT from Microsoft

# About
**Batlang** is a interpreted programming language with nothing new!

# Current State
**Batlang** is very early stage and isn't usable yet<br>
Currently it has:
- Lexer
- Parser
- Error Handler
- Expression Interpreter

# Running
**WARNING:** This was only tested on `Ubuntu`,
	so if you are using a distro not based on `Debian` or `Ubuntu` need to change
	the **Shell** files

## Setup
## Requirements
Make sure to have `g++` or `clang` or `cmake`

```sh
# change clang to g++ if want
sudo apt install clang cmake -y
```

### CMAKE
```sh
mkdir build
cmake -S . -B build
```

## Compiling
## CMAKE
```sh
cmake --build build/
```

### CLANG
```sh
clang++ -std=c++20 -Wall src/*.cpp src/**/*.cpp -leditline -o batlang
```


## Running
> The Shell File Compile **AND** run

### Shell File
```sh
bash setup.sh -g # -g = Compile with clang / -c = Compile with CMake
```

### CMAKE
```sh
cmake --build build
```

### CLANG
```sh
./batlang
```

>`run.sh` compile **and** run (using `cmake`)

# TODO
- [ ] Install support to `Arch` and `Fedora`
- [ ] Remove install of `editline` and put to a `include` instead
- [ ] Better error message

# Credits
Made by me<br>
Inspired by [David Callanan](https://github.com/davidcallanan) and [Matthew Oros](https://github.com/orosmatthew)

