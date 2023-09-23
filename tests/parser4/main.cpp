#include <cstdarg>
#include <iostream>
#include <algorithm>
#include <vector>
#include <regex>

enum class TokenType {
	ROOT,
	SEMICOLON,

	KEYWORD,
	SYMBOL,
	NUMBER,
	STRING,
	SEXPR,
	QEXPR
};

struct Token {
	std::string tag;
	TokenType type;
	std::string value;

	Token* parent;
	std::vector<Token*> child;

	// Constructor
	Token(const std::string& tag, TokenType type, const std::string& value="\0")
		: tag(tag), type(type), value(value), parent(nullptr) {}

	// Destructor
	~Token() {
		for(Token* childToken : child) {
			delete childToken;
		}
	}
};

// "Token" to query and tokenize string
struct TokenQuery {
	std::string tag;
	TokenType type;
	std::string value;
	std::string regex;
	std::vector<TokenType> valid_parents;

	TokenQuery(std::string tag, TokenType type, const std::string& regex, std::vector<TokenType> valid_parents)
		: tag(tag), type(type), regex(regex), valid_parents(valid_parents) {}
};

/* TODO: - To private all that dont needs to stay public */
class Tokenizer {
public:
	Tokenizer() {};

	static Token* make(std::string tag, TokenType type, std::string value="\0", Token* parent=nullptr) {
		Token* token = new Token(tag, type, value);
		if(parent) {
			token->parent = parent;
			parent->child.push_back(token);
		}
		return token;
	}

	static TokenQuery make_token_query(std::string tag, TokenType type, const std::string& regex, std::vector<TokenType> valid_parents) {
		return TokenQuery(tag, type, regex, valid_parents);
	}

	// Print individual
	static std::string print_token(Token* token, int parent_num=0) {
		std::stringstream content;
		std::string tabs(parent_num, ' ');

		content << tabs << token->tag << " | "
			<< ((token->parent) ? '\'' + token->parent->value + '\'' : "0")
			<< ':' << token->child.size()
			<< " |> "
			<< '\'' << token->value << '\'' << "\n";
		// content << tabs << token->tag << std::addressof(token) << " | " << parent << ':' << token->child.size() << " |> " << '\'' << token->value << '\'' << "\n";

		for(Token* childToken : token->child) {
			content << print_token(childToken, parent_num+2); // If have children print each one with tab
		}

		return content.str();
	}

	// Print all
	static std::string print_token(std::vector<Token*> tokens, int parent_num=0) {
		std::stringstream content;

		for(Token* token : tokens) {
			content << print_token(token);
		}

		return content.str();
	}





	static std::string check_regex(std::string content, TokenQuery query) {
		std::vector<Token*> tokens;
		
		std::regex regex(query.regex);

		std::cout << "Regex: " << query.regex << std::endl;
		std::cout << "Content: " << content << std::endl;

		// Check regex
		std::smatch match;
		if (std::regex_search(content, match, regex) && match.position() == 0)
			return match[0].str();
		return "";
	}


	// Tokenize each statement
	static std::vector<Token*> tokenizeStatement(const std::string& content,
												 const std::vector<TokenQuery>& queries, const Token& end_token) {
		std::vector<Token*> tokens;
		std::vector<Token*> opens;
		size_t i = 0;

		while(i < content.length()) {
			char ch = content[i];
			bool token_found = false;

			if(std::isspace(ch)) {
				i++;
				continue;
			}
			
			std::cout << "\nC: " << ch << std::endl;
			if(ch == end_token.value[0]) {
				if(opens.size() > 0) {
					i++;
					continue;
				}

				tokens.push_back(make(end_token.tag, end_token.type, end_token.value));
				i++;
				break;
			}

			if(opens.size() > 0 && ch == opens.back()->value[1]) {
				std::cout << "Found closing " << std::string(1, ch) << std::endl;
				Token* opened = opens.back();
				opened->value = opened->value[0]; // Change '()' to '('
				make(opened->tag, opened->type, std::string(1, ch), opened); // ')' before changing parents

				// Copy all values from last opened to a temp Token, so on push to 'tokens' all childrens goes too
				Token* temp = make(opened->tag, opened->type, opened->value, opened->parent); // '('
				if(opened->child.size() > 0) // Pass all childrens to temp	
					temp->child.insert(temp->child.end(), opened->child.begin(), opened->child.end()); // Change all childrens parents
				// make(opened->tag, opened->type, std::string(1, ch), temp); // ')'

				// Is not necessary to push ')' to tokens, since is child of '('
				tokens.push_back(temp); // '('
				opens.pop_back(); // "Close" last opened

				i++;
				continue;
			}

			for(TokenQuery query : queries) {
				std::cout << "- Current Query: " << query.tag << std::endl;
				if(query.regex[0] == '\\'
					&& content[i] == query.regex[1]
					&& query.regex[query.regex.length() - 2] == '\\') {

					// Make closing token //
					// Add first char from redex, e.g. '('
					// TODO: Decide if use this method or regex[regex.length() - 1]
					std::string value = std::string(1, content[i]) + std::string(1, query.regex[query.regex.length() - 1]);
					opens.push_back(make(query.tag, query.type, value));

					std::cout << query.value << " Expecting to close: " << opens.back()->value << std::endl;

					token_found = true;
					i++; // Next character
					break; // Reset queries (since there is a '(' opened the next character may be a ')', a content or another '()
				}


				std::string found_value = check_regex(content.substr(i), query);
				i += found_value.length();

				if(found_value.empty()) continue; // Not found, try another query
				token_found = true;
				std::cout << "Found: " << found_value << std::endl;

				if(opens.size() > 0) { // If something is open, the next tokens will be childs of it (inside)
					std::cout << "Adding to opened" << std::endl;

					// Parent is last added opened token
					make(query.tag, query.type, found_value, opens.back());
				} else {
					// If last token is a valid parent of current token
					std::cout << "Checking valid parents" << std::endl;
					/*
					std::vector<TokenType>::iterator it =
						std::find(query.valid_parents.begin(), query.valid_parents.end(), tokens.back()->type);
					if(it != query.valid_parents.end()) {
					*/
					tokens.push_back(make(query.tag, query.type, found_value));
				}
	
				break; // Found, reset queries
			}

			// Not foun using any query
			if(!token_found) {
				// TODO: Make a better error handle
				std::cerr << "Invalid keyword" << std::endl;
				exit(EXIT_FAILURE);
			}
		}

		return tokens;
	}


	static std::vector<Token*> tokenize(const std::string& content, const std::vector<TokenQuery>& queries, const Token& end_token) {
		std::vector<Token*> all_tokens;

		// Split the content into statements based on semicolons
		std::vector<std::string> statements;
		size_t start_pos = 0;
		size_t semicolon_pos = content.find(end_token.value[0]);

		while(semicolon_pos != std::string::npos) {
			std::string statement = content.substr(start_pos, (semicolon_pos - start_pos) + 1);

			// Tokenize each statement separately
			std::cout << "\n => STATEMENT => " << statement << std::endl;
			std::vector<Token*> statement_tokens = tokenizeStatement(statement, queries, end_token);
			all_tokens.insert(all_tokens.end(), statement_tokens.begin(), statement_tokens.end());

			// Next statement
			start_pos = semicolon_pos + 1;
			semicolon_pos = content.find(end_token.value[0], start_pos);
		}

		return all_tokens;
	}

	static void free_memory(TokenQuery* query) {
		if(query == nullptr) return;
		delete query;
	}

	static void free_memory(Token* token) {
		if(token == nullptr) return;
		delete token;
	}

	static void cleanup(int n, ...) {
		va_list args;
		va_start(args, n);
		for(int i = 0; i < n; i++) {
			TokenQuery* token = va_arg(args, TokenQuery*);
			delete token;
		}
		va_end(args);
	}

	static void cleanup(const std::vector<Token*> tokens) {
		for(const Token* token : tokens) {
			delete token;
		}
	}
};




int main() {
	std::string content = "exit(123);";

	// Token* root_token = Tokenizer::make("Root", TokenType::ROOT);
	Token semicolon_token("Semicolon", TokenType::SEMICOLON, ";");

	/*
		I'm calling here "Q-Expression" and " S-Expression" just for easy understading
		is not JUST to lisp usage
	*/
	std::vector<TokenQuery> queries = {
		Tokenizer::make_token_query(
			"Keyword", TokenType::KEYWORD,
			"[a-zA-Z_][a-zA-Z0-9_]*", { }
		),

		// Tokenizer::make_token_query(
		// 	"Symbol", TokenType::SYMBOL,
		// 	"", { }
		// ),

		Tokenizer::make_token_query(
			"Number", TokenType::NUMBER,
			"[\\-\\+]?(([0-9]+(\\.[0-9]*)?)|(\\.[0-9]+))", { }
		),

		Tokenizer::make_token_query(
			"QExpr", TokenType::QEXPR,
			"\\([^)]*\\)", { TokenType::KEYWORD }
		),

		// Don't work with it yet
		/*
			Because the tokenizer splits by ';' so with ';' inside '}' the code is splited wrong
			Solution:
				- Make end_token as a string of characters
					* end_token = "};" (priority order)
					* Split string by this characters
		*/
		Tokenizer::make_token_query(
			"Sexpr", TokenType::SEXPR,
			"\\{[^}]*}\\}", { TokenType::KEYWORD }
		)
	};
	std::vector<Token*> tokens = Tokenizer::tokenize(content, queries, semicolon_token);;
	std::cout << Tokenizer::print_token(tokens) << std::endl;

	// Clean all after use
	Tokenizer::cleanup(tokens);
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
