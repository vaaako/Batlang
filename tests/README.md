# Tokenizer
This is a simple C++ tokenizer project developed for educational and learning purposes.
 The main goal of this project is to provide a basic tokenizer in C++ (*split text into tokens*)

## Current Status
This project is in a very early stage of development and still requires many improvements and changes.
 Currently, it is capable of basic text splitting into words but lacks advanced tokenization features.
- [ ] Support for braces
- [ ] Optimization

# Usage
### Compile and run
```sh
g++ -Wall -g -std=c++11 main.cpp -o main # You can also use clang++
./main # Run
```

## Example
String: `exit(123);`
Result:
```
Keyword | 0:0 |> 'exit'
QExpr | 0:2 |> '('
  Number | '(':0 |> '123'
  QExpr | '(':0 |> ')'
Semicolon | 0:0 |> ';'
```

>The example text is the first line of `main` function

### Credits
Made by me<br>
Inspired by [mpc-parser](https://github.com/orangeduck/mpc)