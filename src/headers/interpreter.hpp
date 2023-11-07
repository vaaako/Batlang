#pragma once

#include "context.hpp"
#include "node.hpp"
#include "number.hpp"
#include "result.hpp"

/**
 * This class assembles everything from Lexer and Parser to print a result of all
 * 
 * The nodes start at visit, depending of the type, one of the other visit are executed, interpreted and returns a result
 * */

class Interpreter {
	public:
		Interpreter(Context& context);

		RTResult visit(const Node& node);
		RTResult visit_number(const Node& node);
		RTResult visit_binary(const Node& node);
		RTResult visit_unary(const Node& node);
	private:
		Context& context;
};