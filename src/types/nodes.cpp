#include "../headers/nodes.hpp"
#include <string>

/*
	!left && !right = Number
	left  && right  = Binary Operator
	left  && !right = Unary Operator (so left is the child)
*/

Node::Node(Token token) : token(token), type(NodeType::NUMBER), left(nullptr), right(nullptr) {}
Node::Node(Token token, Node* left, Node* right) : token(token), type(NodeType::BINARY), left(left), right(right) {}
Node::Node(Token token, Node* left) : token(token), type(NodeType::UNARY), left(left), right(nullptr) {}

std::string Node::as_string() {
	if(left == nullptr && right == nullptr)
		return token.as_string();

	return "(" + get_nodes() + ")";
}




NodeType Node::get_type() const {
	return type;
}

Node* Node::get_left() {
	return left;
}

Node* Node::get_right() {
	return right;
}


std::string Node::get_type_as_string(NodeType type) {
	switch (type) {
		case NodeType::NUMBER:
			return "NUMBER";
		case NodeType::BINARY:
			return "BINARY";
		case NodeType::UNARY:
			return "UNARY";
		default: // Never reach (this is just to not get a warning)
			throw std::runtime_error("Node type don't exist");
	}
}


Node::~Node() {
	delete left;
	delete right;
}


/* PRIVATE */
std::string Node::get_nodes() {
	std::string result = "";

	if(left != nullptr)
		result += left->as_string() + " "; // Recursively print left subtree.

	result += token.as_string();

	if(right != nullptr)
		result += " " + right->as_string(); // Recursively print right subtree.

	return result;
}
