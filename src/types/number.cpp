#include "../headers/number.hpp"
#include "../headers/error.hpp"

#include <stdexcept>

Number::Number(const double value) : value(value) {}

EvalResult Number::eval(const double value, const TokenType eval_type, const Position pos) {
	double result;
	switch (eval_type) {
		case TokenType::PLUS:
			result = this->value + value;
			break;
		case TokenType::MINUS:
			result = this->value - value;
			break;
		case TokenType::MUL:
			result = this->value * value;
			break;
		case TokenType::DIV:
			// This is just a test, after I will return as NAN
			if(this->value == 0 && value == 0) return { Error(ErrorType::RuntimeError, pos, "Division by 0") };

			result = this->value / value;
			break;
		default:
			throw std::runtime_error("Invalid operator at Number::eval");
	}

	return { result };
}


/* PRIVATE */
