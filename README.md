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
**WARNING:** This was only tested on `Ubuntu` only,
	so if you are using a distro not based on `Debian` or `Ubuntu`, you need to change
	the **Shell** files

>If you are on windows... Sorry

## Setup
## Requirements
Make sure to have `g++` or `clang` or `cmake`

```sh
# change clang to g++ if you want
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

# Goal
This are some of my goals to this language
### May have changes

## Basics
- Simple
- Statically Typed
- Object-oriented
- Lisp like

## Syntax
I still don't know if I want to use brackets or not

### With
```rust
function is_zero(int y) -> bool {
	let x: int = -1; // Semicolons are optional
	let z: bool = { // Opened context, this is like a lambda
		if x + y == 0 {
			return true;
		} else {
			return false;
		}
	}

	return z;
}
```

### Without
```rust
function is_zero(int y) -> bool then // This "then" is not really necessary, but it's odd without it
	let x: int = -1; // Semicolons are optional
	let z: bool = then // Opened context, this is like a lambda
		if x + y == 0 then
			return true;
		else
			return false;
		end
	end

	return z;
end
```

# Known bugs
- [ ] Unary Nodes give an error when trying to print 

# TODO
- [ ] Install support to `Arch` and `Fedora` on `instal_requirements.sh`
- [ ] Remove install of `editline` and put to a `include` instead
- [ ] Better error message
- [ ] Better context message

# Credits
Made by me<br>
Inspired by [David Callanan](https://github.com/davidcallanan) and [Matthew Oros](https://github.com/orosmatthew)


---
>I'm still learning about `Interpreters` and `C++`, so tell me if I do some mistake

