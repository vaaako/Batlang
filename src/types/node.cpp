#include "../headers/node.hpp"

/*
	!left && !right = Number
	left  && !right = Unary Operator (so left is the child)
	left  && right  = Binary Operator
*/

// Node::Node(const Token token, NodeType type) : token(token), type(NodeType::NUMBER), left(nullptr), right(nullptr), pos(token.get_pos()) {}
// Node::Node(const Token token, Node* left, NodeType type) : token(token), type(NodeType::UNARY), left(left), right(nullptr), pos(left->get_pos()) {}

/*pos_end(right->get_pos())*/
Node::Node(const Token token, Node* left, Node* right, const NodeType type) : token(token), type(NodeType::BINARY), left(left), right(right), pos(token.get_pos()) {
	if(left) this->pos = left->get_pos();

	// Default types
	this->type = (type == NodeType::UNKNOWN) ? 
		((!left && !right) ? NodeType::NUMBER :
		((left && !right) ? NodeType::UNARY :
		((left && right) ? NodeType::BINARY : type))) : type;

	// If still unknown
	// if(type == NodeType::UNKNOWN) std::runtime_error("Node type was not defined");
}

std::string Node::get_type_as_string(const NodeType type) {
	switch (type) {
		case NodeType::NUMBER:
			return "NUMBER";
		case NodeType::BINARY:
			return "BINARY";
		case NodeType::UNARY:
			return "UNARY";
		case NodeType::VARIABLE:
			return "VARIABLE";
		default: // Never reach (this is just to not get a warning)
			throw std::runtime_error("<nodes.cpp> Node type don't exist");
	}
}

/* PRIVATE */

