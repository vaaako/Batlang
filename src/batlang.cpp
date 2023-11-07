#include "headers/batlang.hpp"

#include "headers/batring.hpp"
#include "headers/context.hpp"
#include "headers/lexer.hpp"
#include "headers/result.hpp"
#include "headers/token.hpp"
#include "headers/lexer.hpp"
#include "headers/parser.hpp"
#include "headers/interpreter.hpp"

void Batlang::run(const std::string& filename, const std::string& text, const bool debug) {
	if(text.empty()) return;

	// Generate tokens
	Lexer lexer = Lexer(filename, text);
	LexerResult lexer_result = lexer.make_tokens();

	// If lexer as error
	if(lexer_result.has_error()) {
		Batring::error(lexer_result.get_error());
		return;
	}

	// Generate AST
	Parser parser = Parser(lexer_result.get_value());
	PResult ast = parser.parse();

	// If parser has error
	if(ast.has_error()) {
		Batring::error(ast.get_error());
		return;
	}

	// Run interpreter
	Context context = Context("<program>"); // Make context

	Interpreter interpreter = Interpreter(context);
	RTResult result = interpreter.visit(*ast.get_value());
	/**
	 * Nodes doesn't need to be a pointer, but is much easier to deal with nullptr than optinal
	 * and now is harder to change it
	 * */

	// If interpreter has error
	if(result.has_error()) {
		Batring::error(result.get_error());
		return;
	}


	/* Debug start */
	if(debug) {
		// Show tokens (debug)
		std::cout << "Token: ";
		for(Token token : lexer_result.get_value())
			Batring::result(token.as_string() + " ");

		// Show nodes (debug)
		std::cout << "\nNodes: ";
		Batring::result(ast.get_value()->as_string());

		std::cout << "\n";
	}
	/* Debug end */


	// Show result of interpreter
	Batring::result(result.get_value().as_string());
	std::cout << std::endl;

	// Delete unused node
	// delete ast.get_value();
}
