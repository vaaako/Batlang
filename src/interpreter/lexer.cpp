#include "../headers/lexer.hpp"
#include "../headers/error.hpp"
#include "../headers/token.hpp"

Lexer::Lexer(const std::string& filename, const std::string& text) : text(text), pos(Position(0, 0, 0, filename, text)) {
	if(!text.empty()) cc = pop_text(); // Pop char from text
}

LexerResult Lexer::make_tokens() {
	std::vector<Token> tokens;

	// While text still have char
	while(cc != -1) {
		// Check character //
		if(cc == '\t' || cc == ' ') {
			advance();
			continue;
		} else if (cc == '\n') {
			// Make something on jumping line
			advance();
			continue;
		}


		// Identify //
		if(std::isdigit(cc)) {
			tokens.push_back(make_num());
			continue; // Continue with last peeked char in make_num
			// This is important because if end with ')' it will advance to next character (the end of this loop) and it won't be count
		
		} else if(is_identifier(cc)) {
			tokens.push_back(make_identifier());
			continue; // Same as above

		// Another Character
		} else {
			TokenType tokenType = Token::from_char(cc);

			if(tokenType == TokenType::UNKNOWN)
				return { Error(ErrorType::IllegalCharError, "'" + std::string(1, cc) + "'", pos) };
				// pos-start = pos_start (copy of this->pos) / pos-end = this->pos


			tokens.push_back(Token(tokenType, pos));
		}

		
		advance();
	}

	tokens.push_back(Token(TokenType::TEOF, pos)); // End of File
	return { tokens };
}

Token Lexer::make_identifier() {
	std::string id_str = "";
	// Position pos_start = pos;

	while(cc != -1) {
		if(is_identifier(cc)) id_str += cc;
		else break;

		advance();
	}

	TokenType tok_type = (keywordExists(id_str)) ? TokenType::KEYWORD : TokenType::IDENTIFIER;
	return Token(tok_type, pos, id_str);
}

Token Lexer::make_num() {
	std::string num_str;
	int dot_count = 0;
	// Position pos_start = pos;

	// While not the end
	while(cc != -1) {
		if(std::isdigit(cc)) {
			num_str += cc;
		} else if(cc == '.') {
			if(dot_count == 1) break; // Can't have more than one dot
			dot_count++;
			num_str += '.';
		} else if(cc == '_') {
			advance();
			continue;
		} else { // Not a digit, break loop
			break;
		}

		advance();
	}

	// If is INT or float
	return (dot_count == 0) ? Token(TokenType::INT, pos, static_cast<int>(std::stoi(num_str))) // Converting to Int
		: Token(TokenType::FLOAT, pos, static_cast<double>(std::stod(num_str))); // Converting to Double, so the maximum precision are 6 decimals
	// pos-start = pos_start / pos_end = this->pos


	/**
	 * @WARNING: If changing "double" (Float type) to another type, remember to change at any place that stores value: token, number and batring
	 *           - On changing "int" (Int type) it is only needed to change at "batring", because Integer is only really used on printing (for now)
	 * */

}


bool Lexer::keywordExists(const std::string& target) const {
	for(const std::string& keyword : keywords)
		if (keyword == target) return true; 
	return false;
}