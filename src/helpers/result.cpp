#include "../headers/result.hpp"

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








