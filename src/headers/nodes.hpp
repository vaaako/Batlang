#pragma once

#include "position.hpp"
#include "token.hpp"

#include <string>
#include <locale>
#include <optional>

// This is Unary Node only
#define get_child get_left

enum class NodeType {
	UNKNOWN,
	NUMBER,
	BINARY,
	UNARY
};

class Node {
	public:	
		// Node(Token token, Node* left=nullptr, Node* right=nullptr);
		Node(const Token token);
		Node(const Token token, Node* left, Node* right);
		Node(const Token token, Node* left);

		static std::string get_type_as_string(const NodeType type);

	
		inline NodeType get_type() const {
			return type;
		}

		inline Token get_token() const {
			return token;
		}

		inline Node* get_left() {
			return left;
		}

		inline Node* get_right() {
			return right;
		}

		Position get_pos() {
			return pos;
		}


		inline std::string as_string() const {
			if(left == nullptr && right == nullptr)
				return token.as_string();
			return "(" + get_nodes() + ")";
		}


		~Node();
	private:
		Token token;
		NodeType type = NodeType::UNKNOWN; // Just for the compiler don't complain about

		Node* left;
		Node* right;

		Position pos;


		inline std::string get_nodes() const {
			std::string result = "";

			if(left != nullptr)
				result += left->as_string() + " "; // Recursively print left subtree.

			result += token.as_string();

			if(right != nullptr)
				result += " " + right->as_string(); // Recursively print right subtree.

			return result;
		}
};

