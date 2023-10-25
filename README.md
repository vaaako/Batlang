# Batlang 🦇

Batlang is my Hobby Programming language, making just for learning and fun. It is called Batlang because bat 🦇 is my favorite animal and BAT is in use alredy

>Batlang has no relation with BAT from Microsoft

# About
**Batlang** is a interpreted programming language with nothing new!

# Current State
**Batlang** is very early stage and isn't usable yet<br>
Currently it has:
- Tokenizer
- Parser

# Running
## Setup
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

### G++
```sh
g++ -std=c++20 -Wall src/*.cpp -leditline -o batlang
```


## Running
> The Shell File Compile **AND** run

### Shell File
```sh
bash setup.sh -g # -g = Compile with G++ / -c = Compile with CMake
```

### CMAKE
```sh
cmake --build build
```

### G++
```sh
./batlang
```

>`run.sh` compile **and** run (using `cmake`)

# Credits
Made by me

