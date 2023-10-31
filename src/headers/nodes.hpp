#pragma once

#include "token.hpp"
#include <locale>
#include <optional>

enum class NodeType {
	UNKNOWN,
	NUMBER,
	BINARY,
	UNARY
};

class Node {
	public:	
		// Node(Token token, Node* left=nullptr, Node* right=nullptr);
		Node(Token token);
		Node(Token token, Node* left, Node* right);
		Node(Token token, Node* left);

		std::string as_string();
		~Node();
	private:
		Token token;
		NodeType type = NodeType::UNKNOWN; // Just for the compiler don't complain about

		Node* left;
		Node* right;

		std::string get_nodes();
};

