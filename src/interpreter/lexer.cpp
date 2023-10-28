#include "../headers/lexer.hpp"
#include "../headers/error.hpp"
#include "../headers/token.hpp"

#include <iostream>


Lexer::Lexer(std::string filename, std::string text) : filename(filename), text(text), pos(Position(0, 0, 0, filename, text)) {
	if(!text.empty())
		cc = text[0];
}

void Lexer::advance() {
	pos.advance(cc);
	cc = (pos.get_index() < text.length()) ? text[pos.get_index()] : -1;
	// std::cout << "Advanced to position " << pos.get_index() << " with char: " << cc << std::endl;
}


std::pair<std::vector<Token>, std::optional<Error>> Lexer::make_tokens() {
	std::vector<Token> tokens;

	while(pos.get_index() < text.length()) {
		if(cc == '\t' || cc == ' ') {
			advance();
			continue;
		}

		if(std::isdigit(cc)) {
			Token digit = make_num();
			tokens.push_back(digit);
			continue; // Continue with last checked char in make_num
		} else {
			TokenType tokenType = Token::from_char(cc);

			if(tokenType == TokenType::UNKNOWN)
				return { {}, Error(ErrorType::IllegalCharError, pos, "'" + std::string(1, cc)) };

			tokens.push_back(Token(tokenType, std::string(1, cc), pos));
		}

		
		advance();
	}

	tokens.push_back(Token(TokenType::TEOF, "EOF", pos)); // End of File
	return { tokens, std::nullopt };
}


Token Lexer::make_num() {
	std::string num_str;;
	int dot_count = 0;

	while(pos.get_index() < text.length()) {
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

	// If is INT or float
	if(dot_count == 0)
		return Token(TokenType::INT, num_str, pos);
	else
		return Token(TokenType::FLOAT, num_str, pos);
}
