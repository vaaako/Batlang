#include "headers/batlang.hpp"

#include "headers/lexer.hpp"
#include "headers/token.hpp"
#include "headers/lexer.hpp"
#include "headers/parser.hpp"
#include "headers/interpreter.hpp"

void Batlang::run(const std::string filename, const std::string text, const bool debug) {
	if(text.empty()) return;

	// Generate tokens
	Lexer lexer = Lexer(filename, text);
	LResult lexer_result = lexer.make_tokens();

	// If lexer as error
	if(lexer_result.error.has_value()) {
		Batring::error(lexer_result.error.value());
		return;
	}

	// Generate AST
	Parser parser = Parser(lexer_result.tokens);
	Result ast = parser.parse();

	// If parser has error
	if(ast.has_error()) {
		Batring::error(ast.get_error().value());
		return;
	}

	// Run interpreter
	Interpreter interpreter = Interpreter();
	Number result = interpreter.visit(ast.get_value());
	/**
	 * Nodes don't need to be a pointer, but is much easir to deal with nullptr than optinal
	 * - I need to change later
	 * */


	/* Debug start */
	if(debug) {
		// Show tokens (debug)
		std::cout << "Token: ";
		for(Token token : lexer_result.tokens)
			Batring::result(token.as_string() + " ");

		// Show nodes (debug)
		std::cout << "\nNodes: ";
		Batring::result(ast.get_value()->as_string());

		std::cout << "\n";
	}
	/* Debug end */


	// Show result of interpreter
	Batring::result(result.as_string());
	std::cout << std::endl;

	// Delete unused node
	delete ast.get_value();
}
