#include "../headers/nodes.hpp"

Node::Node(Token token, Node* left, Node* right) : token(token), left(left), right(right) {}

std::string Node::as_string() {
	if(left == nullptr && right == nullptr)
		return token.as_string();

	return "(" + get_nodes() + ")";
}

std::string Node::get_nodes() {
	std::string result = "";

	if(left != nullptr) {
		result += left->as_string(); // Recursively print left subtree.
	}

	result += " " + token.as_string() + " ";

	if(right != nullptr) {
		result += right->as_string(); // Recursively print right subtree.
	}

	return result;
}

Node::~Node() {
	if(left != nullptr) {
		delete left;
		left = nullptr; // Avoid double deletion
	}
	if(right != nullptr) {
		delete right;
		right = nullptr;
	}
}
