#pragma once

#include "error.hpp"
#include "nodes.hpp"

#include <optional>

class Result {
	public:
		Result();

		Result registr(Result res); // Register
		Result set_node(Node* node);
		Result set_error(Error error);
		
		bool has_error();

		std::optional<Error> get_error();
		Node* get_node();
	private:
		std::optional<Error> error;
		Node* node;	
};