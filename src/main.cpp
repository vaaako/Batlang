#include <cstdlib>
#include <iostream>
#include <iterator>
#include <fstream>

#include "headers/batlang.hpp"
#include "headers/editline.h"


// g++ -std=c++20 -Wall src/*.cpp -leditline -o batlang

std::string get_file_contents(const char* filename) {
	std::ifstream in(filename, std::ios::binary); // Read file as binary
	if(!in) throw (errno);

	std::string contents;
	in.seekg(0, std::ios::end);
	contents.resize(in.tellg());
	in.seekg(0, std::ios::beg);
	in.read(&contents[0], contents.size());
	in.close();
	return contents;
}

int main(int argc, char const* argv[]) {
	/* Read file */
	if(argv[1]) { // If not provided a file
		std::string contents = get_file_contents(argv[1]);
		Batlang::run(argv[1], contents, true);

		return 0;
	}


	/* Run interpreter */
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
