#include "../headers/result.hpp"

Result::Result() {}

Result Result::registr(Result res) {
	if(res.has_error())
		error = res.get_error().value();
		// return res.node
	return res;
}


// Sucess (final node)
Result Result::sucess(Node* node) {
	this->node = node;
	return *this;
}

// Failure
Result Result::failure(Error error) {
	this->error = error;
	return *this;
}



/* RTResult */
RTResult::RTResult() {}

RTResult RTResult::registr(RTResult res) {
	if(res.has_error())
		error = res.get_error().value();
		// return res.node
	return res;
}

RTResult RTResult::sucess(double value) {
	this->value = value;
	return *this;
}

RTResult RTResult::failure(Error error) {
	this->error = error;
	return *this;
}




