#include <iostream>
#include <ostream>
#include <string>
#include <errno.h>
#include <stdlib.h>
#include <math.h>

#include "headers/token.h"
#include "headers/lexer.h"

// g++ -std=c++20 -Wall src/*.cpp -leditline -o batlang

/* -= EditLine =- */
// If compiling on Windows compile these functions
#ifdef _WIN32 // _LP64 for linux
#include <string.h>

// Buffer for suer input of size 2048
static char buffer[2048];

// Fake readline function
char* readline(char* prompt) {
	fputs(prompt, stdout);
	fgets(buffer, 2048, stdin);
	char* cpy = malloc(strlen(buffer)+1); // +1 reserved to \0
	strcpy(cpy, buffer);
	cpy[strlen(cpy)-1] = '\0'; // Change last string character to \0
	return cpy;
}

// Fake add_history function (for no errors)
void add_history(char* unused) {}


// Otherwise include the editline header
#else
#include <editline.h> // To be able to use linux arrow keys
#endif
/* -= EditLine =- */




int main() {
	std::cout << "Batlang Version 0.0.1" << std::endl;
	std::cout << "Press Ctrl + C to exit" << std::endl;


	char* input;
	while(true) {
		input = readline("Batlang> ");
	
		// Add input to history
		add_history(input);

		Lexer lexer = Lexer(std::string(input));
		auto result = lexer.make_tokens();

		if(result.second.has_value())
			std::cout << result.second->as_string() << std::endl;
		else
			for(Token token : result.first)
				std::cout << token.print_token() << std::endl;

		// Free input memoru
		delete[] input;
	}
}
