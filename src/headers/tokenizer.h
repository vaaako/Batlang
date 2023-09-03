#pragma once // Just include once (even if used multiple times)

#include <iostream>
#include <algorithm>
#include <optional>
#include <sstream>
#include <vector>

#include "error.h"

enum class TokenType {
	COMMAND,
	INTEGER,  // Integer literal
	SEMICOLON, // Semicoln
};

struct Token {
	TokenType type;
	std::optional<std::string> value;
};




class Tokenizer {
	public:
		/*
			Inline -> Suggest to compiler to insert the body of the function directaly on the code
			 instead of make a call to the function
			 but this is a "suggestion" so the compiler may not do this
		*/
		Tokenizer();
		static std::vector<Token> tokenize(const std::string& content);
	private:
		// ErrorParser error = ErrorParser();
		const std::string m_src;
};