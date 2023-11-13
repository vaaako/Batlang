#include <iostream>
#include <iterator>

#include "headers/batlang.hpp"
#include "headers/editline.h"


// g++ -std=c++20 -Wall src/*.cpp -leditline -o batlang


int main() {
	std::cout << "Batlang Version 0.1" << std::endl;
	std::cout << "Press Ctrl + C or type \"exit\" to exit" << std::endl;


	std::string input;
	while(true) {
		input = readline("Batlang> ");
	
		// Add input to history
		add_history(input.c_str());

		if(input.length() > 0 && input == "exit") break;

		// Run (duurh)
		Batlang::run("<stdin>", std::string(input), true);
		
		// Free input memory
		// delete[] input;
	}
}
