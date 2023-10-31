#include "../headers/nodes.hpp"

/*
	!left && !right = Number
	left  && right  = Binary Operator
	left  && !right = Unary Operator (will not print as it is, but it is)
*/

Node::Node(Token token) : token(token), type(NodeType::NUMBER), left(nullptr), right(nullptr) {}
Node::Node(Token token, Node* left, Node* right) : token(token), type(NodeType::BINARY), left(left), right(right) {}
Node::Node(Token token, Node* left) : token(token), type(NodeType::UNARY), left(left), right(nullptr) {}

std::string Node::as_string() {
	if(left == nullptr && right == nullptr)
		return token.as_string();

	return "(" + get_nodes() + ")";
}

std::string Node::get_nodes() {
	std::string result = "";

	if(left != nullptr)
		result += left->as_string() + " "; // Recursively print left subtree.

	result += token.as_string();

	if(right != nullptr)
		result += " " + right->as_string(); // Recursively print right subtree.

	return result;
}

Node::~Node() {
	delete left;
	delete right;
}
