#include "../headers/lexer.hpp"
#include "../headers/error.hpp"
#include "../headers/token.hpp"

#include <iostream>
#include <string>


Lexer::Lexer(std::string filename, std::string text) : text(text), pos(Position(0, 0, 0, filename, text)) {
	if(!text.empty())
		cc = text[0];
}

void Lexer::advance() {
	pos.advance(cc);
	cc = (pos.get_index() < text.length()) ? text[pos.get_index()] : -1;
	// std::cout << "Advanced to position " << pos.get_index() << " with char: " << cc << std::endl;
}


LResult Lexer::make_tokens() {
	std::vector<Token> tokens;

	while(pos.get_index() < text.length()) {
		if(cc == '\t' || cc == ' ') {
			advance();
			continue;
		}

		if(std::isdigit(cc)) {
			Token digit = make_num();
			tokens.push_back(digit);
			continue; // Continue with last peeked char in make_num
		} else {
			TokenType tokenType = Token::from_char(cc);

			if(tokenType == TokenType::UNKNOWN)
				return { Error(ErrorType::IllegalCharError, pos, "'" + std::string(1, cc) + "'") };

			tokens.push_back(Token(tokenType, pos));
		}

		
		advance();
	}

	tokens.push_back(Token(TokenType::TEOF, pos)); // End of File
	return { tokens };
}


Token Lexer::make_num() {
	std::string num_str;
	int dot_count = 0;

	// While not the end
	while(pos.get_index() != -1) {
		if(std::isdigit(cc)) {
			num_str += cc;
		} else if(cc == '.') {
			if(dot_count == 1) break; // Can't have more than one dot
			dot_count++;
			num_str += '.';
		} else { // Not a digit, break loop
			break;
		}

		advance();
	}

	// If is INT or float
	return (dot_count == 0) ? Token(TokenType::INT, pos, std::stoi(num_str)) // Converting to Int
		: Token(TokenType::FLOAT, pos, std::stod(num_str)); // Converting to Double, so the maximum precision are 6 decimals
	/**
	 * @WARNING: If changing "stod" (Float type) to another type, remember to change at any place that stores value: token, number and batring
	 *           - On changing "stoi" (Int type) it is only needed to change at "batring", because Integer is only really used on printing (for now)
	 * */

}
