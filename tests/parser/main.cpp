#include <iostream>
#include <regex>
#include <vector>
#include <string>


enum class TokenType {
	ROOT,
	KEYWORD,
	NUMBER,
	STRING,
	SEXPR,
	QEXPR,
	SEMICOLON
};

class Token {
	public:
		Token(std::string tag, TokenType type, std::string value)
			: tag(tag), type(type), value(value), parent(nullptr) {}

		std::string tag;
		TokenType type;
		std::string value;
		Token* parent;
		std::vector<Token> child;  // Use um vetor para representar filhos
};

struct TokenQuery {
	TokenQuery(std::string tag, TokenType type, std::string regex, std::vector<TokenType> parents)
		: regex(std::regex(regex)), tag(tag), type(type), parents(parents) {}

	std::regex regex;
	std::string tag;
	TokenType type;
	std::vector<TokenType> parents;
};

Token make_token(std::string tag, TokenType type, std::string value) {
	return Token(tag, type, value);
}


// void query_tokens(std::vector<TokenQuery>& to_query, std::string content, Token* parent) {
//     for (const auto& query : to_query) {
//         std::smatch match;
//         while (std::regex_search(content, match, query.regex)) {
//             Token new_token = make_token(query.tag, query.type, match[0]);
//             new_token.parent = parent;
//             parent->child.push_back(new_token);
//             content = match.suffix();  // Avance para o próximo trecho de texto
//             query_tokens(to_query, content, &new_token);  // Recursão para tokens filhos
//         }
//     }
// }
 


void query_tokens(std::vector<TokenQuery> to_query, std::string content, Token* parent) {
	std::vector<Token> tokens;

	size_t pos = content.find(";");
	if(pos == std::string::npos) {
		std::cout << "Nenhum ; achado " << pos << std::endl;
	}
	content = content.substr(0, pos + 1);
	std::cout << "Content: " << content << std::endl;


	for(const auto& query : to_query) {
		std::smatch match;
		std::cout << "\n--------\nQuering: " << query.tag << std::endl;

		while(std::regex_search(content, match, query.regex)) {

			for(int i=0; i < match.size(); i++) {
				std::cout << "Find: " << match[i] << "\nTag: " << query.tag << std::endl;
			}
			std::cout << "Keyword: " << match[0] << std::endl;
			content = match.suffix();

			Token new_token = make_token(query.tag, query.type, match[0]);

			bool found = false;
			if(query.parents.size() > 0)
				found = std::find(query.parents.begin(), query.parents.end(), tokens.back().type) != query.parents.end(); 
			// 	std::cout << "Parent: " << tokens.back().tag << std::endl;
			// new_token.parent = parent;


			// Token new_token = make_token(query.tag, query.type, match[0]);
			// if(tokens.back().type == TokenType::ROOT) {
			// 	new_token.parent = &tokens[0];
			// }



			// if(tokens.back().type == TokenType::ROOT){
			// 	new_token.parent = &tokens[0];
			// } else if(query.parents.size() == 0
			// 	|| std::find(query.parents.begin(), query.parents.end(), tokens.back().type) != query.parents.end())
			// {
			// 	std::cout << "Parent: " << tokens.back().tag << std::endl;
				
			// 	new_token.parent = &tokens.back();
			// 	tokens.back().child.push_back(new_token);

			// 	content = match.suffix();
			// 	query_tokens(to_query, content);  // Recursão para tokens filhos
			// }
		}
	}
}

int main() {
	std::vector<TokenQuery> queries = {
		TokenQuery("keyword", TokenType::KEYWORD, "[a-zA-Z_][a-zA-Z0-9_]*", { }),
		TokenQuery("sexpr", TokenType::SEXPR, "\\([^)]*\\)", { TokenType::KEYWORD, TokenType::SEXPR, TokenType::NUMBER }),
		TokenQuery("number", TokenType::NUMBER, "[\\-\\+]?(([0-9]+(\\.[0-9]*)?)|(\\.[0-9]+))", { }),
	};

	std::string content = "exit (1); test(2); \nteest(3)";

	Token root_token("Root", TokenType::ROOT, "");  // Crie um token raiz
	query_tokens(queries, content, &root_token);

	// Agora, você pode percorrer a árvore de tokens hierarquicamente
	// Exemplo: Imprimir tokens e seus filhos
	for (const Token& token : root_token.child) {
		std::cout << "Parent: " << token.tag << std::endl;

		for (const Token& chi : token.child) {
			std::cout << "-> Child: " << chi.tag << std::endl;
		}
	}

	return 0;
}

/*










Todo objeto (Bat) começa com um símbolo:
let x = 1;
func main()

A base vai ser parecida com altbat
- Altbat objeto principal
- Criar objeto pra cada keyword ou {} ou ()

- Fazer um while loop por linha
- Procurar por um símbolo usando regex.search
- Caso ache um simbolo
	- Criar objeto de simbolo

- Senão, procurar por {}
- Tentar fazer algo tipo o mpc_parser
altbat
	-> symb |> let
		- symb | symb->child(0) |> x
		- symb | symb->child(1) |> =
		- symb | symb->child(2) |> 123;
-> semicolon

altbat
	-> symb |> print
		-> qexpr | child(0) |> '('
			-> string | qexpr.child(0) | symb.child(1) |> "hello"
		-> qexpr | child(1) |> ')'
-> semicolon

*/