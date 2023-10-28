#include "../headers/result.hpp"
#include <optional>

Result::Result() {}

Result Result::registr(Result res) {
	if(res.has_error())
		error = res.get_error().value();
		// return res.node
	return res;
}


// Sucess (final node)
Result Result::set_node(Node* node) {
	this->node = node;
	return *this;
}

// Failure
Result Result::set_error(Error error) {
	this->error = error;
	return *this;
}


bool Result::has_error() {
	return (error.has_value()) ? true : false;
}




std::optional<Error> Result::get_error() {
	return error;
}

Node* Result::get_node() {
	return node;
}

