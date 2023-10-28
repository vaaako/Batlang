#pragma once

#include "token.hpp"
#include <locale>
#include <optional>

class Node {
	public:	
		Node(Token token, Node* left=nullptr, Node* right=nullptr);

		std::string as_string();
		~Node();
	private:
		Token token;

		Node* left;
		Node* right;

		std::string get_nodes();
};
