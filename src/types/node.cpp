#include "../headers/node.hpp"

/*
	!left && !right = Number
	left  && !right = Unary Operator (so left is the child)
	left  && right  = Binary Operator
*/

Node::Node(const Token token) : token(token), type(NodeType::NUMBER), left(nullptr), right(nullptr), pos(token.get_pos()) {}
Node::Node(const Token token, Node* left) : token(token), type(NodeType::UNARY), left(left), right(nullptr), pos(left->get_pos()) {}
Node::Node(const Token token, Node* left, Node* right) : token(token), type(NodeType::BINARY), left(left), right(right), pos(left->get_pos()) /*pos_end(right->get_pos())*/ {}

std::string Node::get_type_as_string(const NodeType type) {
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

/* PRIVATE */

