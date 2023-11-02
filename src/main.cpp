#include <iostream>
#include <iterator>

#include "headers/token.hpp"
#include "headers/lexer.hpp"
#include "headers/parser.hpp"
#include "headers/interpreter.hpp"

#include "headers/editline.h"


// g++ -std=c++20 -Wall src/*.cpp -leditline -o batlang

void run(const std::string filename, const std::string text) {
	if(text.empty()) return;

	// Generate tokens
	Lexer lexer = Lexer(filename, text);
	LResult lexer_result = lexer.make_tokens();

	// If lexer as error
	if(lexer_result.error.has_value()) {
		std::cout << lexer_result.error->as_string() << std::endl;
		return;
	}

	// Generate AST
	Parser parser = Parser(lexer_result.tokens);
	Result ast = parser.parse();

	// If parser has error
	if(ast.has_error()) {
		std::cout << ast.get_error().value().as_string() << std::endl;
		return;
	}

	// Show nodes (debug)
	// std::cout << ast.get_node()->as_string() << std::endl;


	// Run interpreter
	Interpreter interpreter = Interpreter();
	Number* result = interpreter.visit(ast.get_node());

	std::cout << Batring::result(result->as_string()) << std::endl;
	// std::cout << "Token: ";
	// for(Token token : tokens.first)
	// 	std::cout << token.as_string() << " ";
	// std::cout << std::endl;

	// Delete unused node
	delete ast.get_node();
	delete result;
}

int main() {
	std::cout << "Batlang Version 0.1" << std::endl;
	std::cout << "Press Ctrl + C to exit" << std::endl;


	char* input;
	while(true) {
		input = readline("Batlang> ");
	
		// Add input to history
		add_history(input);

		// Run (duurh)
		run("<stdin>", std::string(input));
		
		// Free input memory
		delete[] input;
	}
}
