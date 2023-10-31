#pragma once

#include "nodes.hpp"

class Interpreter {
	public:
		Interpreter();

		void visit(NodeType node_type);
		void visit_number();
		void visit_binary();
		void visit_unary();
	private:
};