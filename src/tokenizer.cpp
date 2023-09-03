#include "headers/tokenizer.h"

// Tokenizer::Tokenizer(const std::string& src) : m_src(std::move(src)) { // -> m_src equal to src / std::move() -> moves the value to another var (more efficient if not using the original var)
// }
Tokenizer::Tokenizer() {}

// Just used to map tokens
struct TokenMap {
	enum TokenType type;
	std::string keyword;
} token_map[] = {
	{ TokenType::COMMAND, "exit" }
};

std::vector<Token> Tokenizer::tokenize(const std::string& content) {
	std::vector<Token> tokens; // To store all tokens
	std::string word; // Buffer string
	bool lastWordHasSemicolon = false;

	std::stringstream ss(content);

	// Word by word
	while(ss >> word) {
		if(word.empty()) continue; // Skip empty tokens
		if(word.back() == ';') { // Has semicolon as last character	
			word = word.substr(0, word.size() - 1);
			// word.pop_back(); // Remove the semicolon from the end
			lastWordHasSemicolon = true;
		}

		// Check if word is a number
		bool isNumber = true;
		for(char c : word) {
			if(!std::isdigit(c)) { // If have something else is not a number
				isNumber = false;
				// break;
			}
		}

		if(isNumber) {
			// Check if the word contains non-numeric characters in the middle
			for (char c : word) {
				if (!std::isdigit(c)) {
					ErrorParser::throw_error("Invalid number", word);
				}
			}

			tokens.push_back({ .type = TokenType::INTEGER, .value = word });
		} else {
			// Use a lookup table to check if word is some command (using token_map)
			auto it = std::find_if(std::begin(token_map), std::end(token_map), [&word](const TokenMap& map) {
				return map.keyword == word;
			});

			// If it don't reach the end of token_map (find something)
			if(it != std::end(token_map)) { 
				// tokens.push_back({ .type = it->type });
				tokens.push_back({ .type = it->type, .value = word });
			} else {
				ErrorParser::throw_error("Invalid keyword", word);
			}

		}

		if(lastWordHasSemicolon) tokens.push_back({ .type = TokenType::SEMICOLON }); // Add semicolon to the end
	}

	if(!lastWordHasSemicolon) ErrorParser::throw_error("No semicolon found!");
	return tokens;
}