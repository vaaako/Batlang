#include <algorithm>
#include <cctype>
#include <cstdarg>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sys/types.h>
#include <vector>
#include <regex>

enum class TokenQueryType {
	ROOT,
	SEMICOLON
};

enum class TokenType {
	ROOT,
	SEMICOLON,

	KEYWORD,
	SYMBOL,
	NUMBER,
	STRING,
	SEXPR,
	QEXPR,
};

struct Token {
	std::string tag;
	TokenType type;
	std::string value;

	std::vector<Token*> parent;
	std::vector<Token*> child;

	// Destructor
	// ~Token() {
	// 	for(Token* childToken : child) {
	// 		delete childToken;
	// 	}
	// }
};

// struct TokenQuery;
// typedef struct TokenQuery TokenQuery;
struct TokenQuery {
	struct Token* token;
	std::string regex;
};

/* TODO: - To private all that dont needs to stay public
		 - Remove all uncessary static
		 ? Make to Constructor (then all functions will be methods) */
class Tokenizer {
public:
	Tokenizer() {};

	static Token* make(std::string tag, TokenType type, std::string value="\0") {
		Token* x = new Token();
		x->tag = tag;
		x->type = type;
		x->value = value;
		return x;
	}

	static TokenQuery* make_token_query(Token* token, std::string regex) {
		TokenQuery* x = new TokenQuery();
		x->token = token;
		x->regex = regex;
		return x;
	}

	static std::string print_token(Token* token, int parent_num=0) {
		std::stringstream content;
		std::string tabs;

		for(int i = 0; i < parent_num; i++) {
			tabs += "   ";
		}

		content << tabs << token->tag << " | " << token->parent.size() << ':' << token->child.size() << " |> " << '\'' << token->value << '\'';
		content << "\n";

		for(int i = 0; i < (int)token->child.size(); i++) {
			// for(Token* childToken : token->child) {

			Token* childToken = token->child[i];
			content << print_token(childToken, (int)childToken->parent.size());
		}

		return content.str();
	}

	static std::string print_token(std::vector<Token*> tokens, int parent_num=0) {
		std::stringstream content;

		for(Token* token : tokens) {
			content << print_token(token);
		}

		return content.str();
	}

	static std::string check_regex(std::string content, TokenQuery* query) {
		std::vector<Token*> tokens;
		
		std::regex regex(query->regex);

		std::cout << "Regex: " << query->regex << std::endl;
		std::cout << "Content: " << content << std::endl;

		std::string tokenregex = query->regex;

		// Check regex
		std::smatch match;
		if (std::regex_search(content, match, regex) && match.position() == 0)
			return match[0].str();
		return "";
	}

	static std::vector<Token*> tokenize(std::string content, std::vector<TokenQuery*> queries, Token* end_token) {
		std::vector<Token*> tokens;

		size_t i = 0;
		std::vector<TokenQuery*> opens; // When something is open ('(' or '{') this will store the expected character to close opened character
		while(i < content.length()) {
			char ch = content[i];
			bool token_found = false;

			if(std::isspace(ch)) {
				i++;
				continue;
			}
			
			std::cout << "\nC: " << ch << std::endl;
			if(ch == end_token->value[0]) {
				tokens.push_back(end_token);
				i++;
				break;
			}

			// if(expecting_to_close && std::to_string(ch) == expecting_to_close->value) {
			if(opens.size() > 0 && ch == opens[0]->regex[opens[0]->regex.length() - 1]) {
				std::cout << "Found closing" << std::endl;
				Token* token = opens[0]->token;

				Token* temp = new Token();
				temp->tag = token->tag;
				temp->type = token->type;
				temp->value = opens[0]->regex[opens[0]->regex.length() - 1];

				temp->parent.push_back(token);
				token->child.push_back(temp);

				// tokens.push_back(tem;
				opens.pop_back(); // "Close" last opened

				// delete temp;
				i++;
				continue;
			}

			for(TokenQuery* query : queries) {
				std::cout << "- Current Query: " << query->token->tag << std::endl;
				std::string tokenregex = query->regex;
				if(tokenregex[0] == '\\' && content[i] == tokenregex[1]) {
					Token* token = query->token;
					token->value = content[i]; // -> e.g. '('

					// Make closing token
					tokens.push_back(token);
					opens.push_back(query);
					std::cout << token->value << " Expecting to close: " << opens[0]->regex[opens[0]->regex.length() - 1] << std::endl;

					token_found = true;
					i++; // Next character
					break; // Reset queries (since there is a '(' opened the next character may be a ')', a content or another '()
				}


				std::string found_value = Tokenizer::check_regex(content.substr(i), query);
				i += found_value.length();
				if(found_value.empty()) continue;

				token_found = true;
				std::cout << "Found: " << found_value << std::endl;

				query->token->value = found_value;
				if(opens.size() > 0) { // If something is open, the next tokens will be childs of it (inside)
					std::cout << "Adding to temp" << std::endl;
					query->token->parent.push_back(opens[0]->token); // Add to last opened token
					opens[0]->token->child.push_back(query->token);
				} else {
					tokens.push_back(query->token);
				}

				// Found, reset queries
				break;
			}

			if(!token_found) {
				std::cerr << "Invalid keyword" << std::endl;
				exit(EXIT_FAILURE);
			}
		}

		return tokens;
	}


	static void free_memory(TokenQuery* query) {
		if(query == nullptr) return;
			// for(Token* queryToken : query->token) { 
			// free_memory(query->token);
			// }
		delete query;
	}

	static void free_memory(Token* token) {
		if(token == nullptr) return;
			// for(Token* childToken : token->child) {
			// 	free_memory(childToken);
			// }
		delete token;
	}

	static void cleanup(int n, ...) {
		va_list args;
		va_start(args, n);
		for(int i = 0; i < n; i++) {
			TokenQuery* token = va_arg(args, TokenQuery*);
				// print_token(token);
			free_memory(token);
		}
		va_end(args);
	}

private:
};




int main() {
	std::string content = "exit(123); return(123);";

	Token* root_token = Tokenizer::make("Root", TokenType::ROOT);
	Token* keyword_token = Tokenizer::make("Keyword", TokenType::KEYWORD);
	Token* qexpr_token = Tokenizer::make("QExpr", TokenType::QEXPR);
	Token* number_token = Tokenizer::make("Number", TokenType::NUMBER);
	Token* semicolon_token = Tokenizer::make("Semicolon", TokenType::SEMICOLON, ";");

	TokenQuery* keyword_query = Tokenizer::make_token_query(keyword_token, "[a-zA-Z_][a-zA-Z0-9_]*");
	TokenQuery* number_query = Tokenizer::make_token_query(number_token, "[\\-\\+]?(([0-9]+(\\.[0-9]*)?)|(\\.[0-9]+))");
	TokenQuery* qexpr_query = Tokenizer::make_token_query(qexpr_token, "\\([^)]*\\)");

	std::vector<TokenQuery*> queries = { keyword_query, qexpr_query, number_query };

	std::vector<Token*> tokens = Tokenizer::tokenize(content, queries, semicolon_token);;

	std::cout << Tokenizer::print_token(tokens) << std::endl;
	
	// Tokenizer::cleanup(3, keyword_query, qexpr_query, number_query);
	// Tokenizer::cleanup(5, keyword_token, qexpr_token, number_token, semicolon_token, temp);
}

/*
root
	-> symb |> let
		- symb | symb->child(0) |> x
		- symb | symb->child(1) |> =
		- symb | symb->child(2) |> 123;
	-> semicolon
root

- Split into ';'
	*  "print(); exit();" -> [ "print();", "exit();" ] 
- Go through each string
- Check regex
	* char by char until don't match regex
	* Ex.: Qexpr valid parents => KEYWORD, ROOT (Priority order)
	* Search between last ROOT and SEMICOLON for any of parents
		+ Is valid if found KEYWORD (then add as child of this keyword) or if find ROOT, else is not valid
- When reach SEMICOLON, go to next block
*/
