# Batlang
Batlang is my Hobby Programming language, making just for learning and fun.
 It is called **Batlang** because I like bats :bat: and **BAT** is in use alredy

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

### Credits
Made by me<br>
 Inpired by [orosmatthew](https://github.com/orosmatthew/hydrogen-cpp)
