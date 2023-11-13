#include "../headers/number.hpp"
#include "../headers/error.hpp"

#include <cmath>
#include <stdexcept>

Number::Number(const double value) : value(value) {}
Number::Number(const double value, const Position& pos) : value(value), pos(pos) {}
Number::Number(const double value, const Context& context) : value(value), context(context) {}
Number::Number(const double value, const Position& pos, const Context& context) : value(value), pos(pos), context(context) {}


EvalResult Number::eval(const double value, const TokenType eval_type, const Position& pos) {
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
			if(this->value == 0 && value == 0) return { Error(ErrorType::RuntimeError, "Division by 0", pos, context.value()) };

			result = this->value / value;
			break;
		case TokenType::POW:
			result = std::pow(this->value, value);
			break;
		default:
			throw std::runtime_error("Invalid operator at Number::eval");
	}


	return { result };
}


/* PRIVATE */
