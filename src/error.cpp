#include "headers/error.h"

Error::Error(std::string name, std::string details) : name(name), details(details) {}

std::string Error::as_string() {
	return this->name + ": " + this->details;
}



IllegalCharError::IllegalCharError(std::string details) : Error("Illegal Character", details) {}
