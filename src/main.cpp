
#include <iostream>
#include <algorithm>
#include <fstream>
#include <optional>
#include <sstream>
#include <vector>

#include "headers/tokenizer.h"
#include "headers/error.h"

std::string tokens_to_asm(const std::vector<Token>& tokens) {
	std::stringstream output;
	output << "global _start\n_start:\n";

	for (size_t i = 0; i < tokens.size() - 2; i++) {
		const Token& token = tokens[i];

		// if(tokens[tokens.size() - 1].type != TokenType::SEMICOLON) {
		// 	throw_error("No semicolon found!");
		// }

		if(token.type == TokenType::COMMAND) {
			if(token.value == "exit" && tokens[i + 1].type == TokenType::INTEGER) {
				output << "\tmov rax, 60\n";
				output << "\tmov rdi, " << tokens[i + 1].value.value() << "\n";
				output << "\tsyscall\n";

				i += 2; // Skip the processed tokens
				break; // Is exit, so break everything else
			}
		}
	}

	return output.str();
}





std::string get_file_contents(const char *filename) {
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
	if(!argv[1]) { // If not provided a file
		std::cout << "You have to provide a .bt file" << std::endl;
		std::cout << "Ex.: bat <file.bt>" << std::endl;
		return EXIT_FAILURE;
	}

	std::string contents = get_file_contents(argv[1]).c_str();
	// std::string contents;
	// {
	// 	std::stringstream contents_stream;
	// 	std::fstream input(argv[1], std::ios::in);
	// 	contents_stream << input.rdbuf();
	// 	contents = contents_stream.str();
	// }
	// std::cout << contents << std::endl;

	// std::vector<Token> tokens = Tokenizer::tokenize(contents);
	// Tokenizer tokenizer = Tokenizer();
	std::vector<Token> tokens = Tokenizer::tokenize(contents);

	{
		std::fstream file("out.asm", std::ios::out); // Closes automatically since is inside a scope
		file << tokens_to_asm(tokens);
	}

	system("nasm -f elf64 out.asm");
	system("ld out.o -o out");
}
