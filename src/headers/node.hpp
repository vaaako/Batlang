#pragma once

#include "position.hpp"
#include "token.hpp"

#include <algorithm>
#include <string>
#include <locale>
#include <optional>

// This is Unary Node only
#define get_child get_left

enum class NodeType {
	UNKNOWN,
	NUMBER,
	BINARY,
	UNARY,
	VARIABLE
};


/**
 * This class takes a token and (optional) two other Nodes to assemble
 * in a single value
 * e.g. [INT:1 MUL:* [INT:2 PLUS:+ INT:2]]
 * 
 * [] - Represents a node
 * */

class Node {
	public:	
		Node(const Token token, Node* left=nullptr, Node* right=nullptr, const NodeType type=NodeType::UNKNOWN);
		static std::string get_type_as_string(const NodeType type);

	
		inline NodeType get_type() const {
			return type;
		}

		inline Token get_token() const {
			return token;
		}

		inline const Node& get_left() const {
			return *left;
		}

		inline const Node& get_right() const {
			return *right;
		}

		inline Position get_pos() const {
			return pos;
		}


		inline std::string as_string() const {
			if(left == nullptr && right == nullptr)
				return token.as_string();
			return "(" + get_nodes() + ")";
		}


		~Node() {
			delete left;
			delete right;
		}
	private:
		Token token;
		NodeType type = NodeType::UNKNOWN; // Just for the compiler don't complain about

		Node* left;
		Node* right;

		Position pos;


		inline std::string get_nodes() const {
			std::string result = "";

			if(left != nullptr) // Error here
				result += left->as_string() + " "; // Recursively print left subtree.

			result += token.as_string();

			if(right != nullptr)
				result += " " + right->as_string(); // Recursively print right subtree.

			return result;
		}
};

