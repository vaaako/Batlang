# Batlang :bat:
Batlang is my Hobby Programming language, making just for learning and fun.
 It is called **Batlang** because bat :bat: is my favorite anumal
 and **BAT** is in use alredy
>Batlang has no relation with BAT from Microsoft

# Running
## Install requirements
**Batlang** requires `nasm` and `ld`

```sh
sudo apt install nasm
```

>ld should be installed by default

## Building
```sh
git clone https://github.com/vaaako/batlang
cd batlang
```

### CMAKE
```sh
mkdir build
cmake -S . -B build
cmake --build build
```
The executable file (`bat`) will be in `build/` directory

### G++
```sh
g++ src/main.cpp src/*.cpp -o bat
```

### TESTING
You can test it by running
```sh
./build/bat test.bt
```

If compiled using `g++`
```sh
./bat test.bt
```

# Current State
The language isn't usable yet
`Batlang` has:
- Tokenizer
- Compiler to `ASM`

### Credits
Made by me<br>
 Inpired by [orosmatthew](https://github.com/orosmatthew/hydrogen-cpp)
