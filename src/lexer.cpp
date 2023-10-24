#include "headers/lexer.h"
#include "headers/error.h"
#include "headers/token.h"
#include <cctype>
#include <charconv>
#include <iostream>
#include <cstddef>
#include <cstring>
#include <optional>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

Lexer::Lexer(std::string text) : text(text) {
	if(!text.empty())
		cc = text[0];
}

void Lexer::advance() {
	pos++;
	cc = (pos < text.length()) ? text[pos] : -1;
	std::cout << "Advanced to position " << pos << " with char: " << cc << std::endl;
}


std::pair<std::vector<Token>, std::optional<Error>> Lexer::make_tokens() {
	std::vector<Token> tokens;

	while(pos < text.length()) {

		if(cc == '\t' || cc == ' ') {
			advance();
			continue;
		}

		if(std::isdigit(cc)) {
			Token digit = make_num();
			tokens.push_back(digit);
		} else {
			TokenType tokenType = Token::from_char(cc);

			if(tokenType == TokenType::UNKNOWN) {
				return { {}, IllegalCharError("'" + std::string(1, cc) + "' at position " + std::to_string(pos)) };
			}

			tokens.push_back(Token(tokenType, std::string(1, cc)));
		}

		
		advance();
	}

	std::cout << "Token count: " << tokens.size() << std::endl;
	return { tokens, std::nullopt };
}


Token Lexer::make_num() {
	std::string num_str;;
	int dot_count = 0;

	while(pos < text.length()) {
		if(std::isdigit(cc)) {
			num_str += cc;
		} else if(cc == '.') {
			if(dot_count == 1) break; // Can't have more than one dot
			dot_count++;
			num_str += '.';
		} else {
			break;
		}

		advance();
	}


	if(dot_count == 0) {
		return Token(TokenType::INT, num_str);
	} else {
		return Token(TokenType::FLOAT, num_str);
	}
}
