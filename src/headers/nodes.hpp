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

		static std::string get_type_as_string(NodeType type);
		NodeType get_type() const;

		~Node();
	private:
		Token token;
		NodeType type = NodeType::UNKNOWN; // Just for the compiler don't complain about

		Node* left;
		Node* right;

		std::string get_nodes();
};

