#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <optional>
#include <string>
#include <sstream>
#include <vector>

enum class TokenType {
	COMMAND,
	INTEGER,  // Integer literal
	SEMICOLON, // Semicoln
};

struct Token {
	TokenType type;
	std::optional<std::string> value;
};


// Just used to map tokens
struct TokenMap {
	enum TokenType type;
	std::string keyword;
} token_map[] = {
	{ TokenType::COMMAND, "return" }
};


void throw_error(const std::string& err_message, std::string value="") {
	std::string formated_value = " ";
	if(value.length() > 0)
		formated_value = " '" + value + "'";

	std::cerr << err_message << formated_value << std::endl;
	exit(EXIT_FAILURE);
}

std::vector<Token> tokenize(const std::string& content) {
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
					throw_error("Invalid number", word);
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
				throw_error("Invalid keyword", word);
			}

		}

		if(lastWordHasSemicolon) tokens.push_back({ .type = TokenType::SEMICOLON }); // Add semicolon to the end
	}

	if(!lastWordHasSemicolon) throw_error("No semicolon found!");
	return tokens;
}



std::string tokens_to_asm(const std::vector<Token>& tokens) {
	std::stringstream output;
	output << "global _start\n_start:\n";

	for (size_t i = 0; i < tokens.size() - 2; i++) {
		const Token& token = tokens[i];


		if(token.type == TokenType::COMMAND) {
			if(token.value == "return" && tokens[i + 1].type == TokenType::INTEGER) {
				output << "\tmov rax, 60\n";
				output << "\tmov rdi, " << tokens[i + 1].value.value() << "\n";
				output << "\tsyscall\n";

				i += 2; // Skip the processed tokens
			}
		}
	}

	return output.str();
}



int main() {
	std::string input = "ex 69";
	char delimiter = ' '; // O espaço em branco é usado como delimitador

	std::vector<Token> tokens = tokenize(input);

	// Imprime os tokens
	for (Token& token : tokens) {
		std::cout << "Type: " << (int)token.type << std::endl;
	}
	std::cout << tokens_to_asm(tokens) << std::endl;

	return 0;
}
