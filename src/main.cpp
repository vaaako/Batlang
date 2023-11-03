#include <iostream>
#include <iterator>

#include "headers/batlang.hpp"
#include "headers/editline.h"


// g++ -std=c++20 -Wall src/*.cpp -leditline -o batlang


int main() {
	std::cout << "Batlang Version 0.1" << std::endl;
	std::cout << "Press Ctrl + C to exit" << std::endl;


	char* input;
	while(true) {
		input = readline("Batlang> ");
	
		// Add input to history
		add_history(input);

		// Run (duurh)
		Batlang::run("<stdin>", std::string(input), true);
		
		// Free input memory
		delete[] input;
	}
}
