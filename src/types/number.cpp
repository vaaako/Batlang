#include "../headers/number.hpp"
#include <stdexcept>

Number::Number(const double value) : value(value) {}

// Generic = Int | Float
Number Number::eval(const double value, const TokenType eval_type) {
	// bool is_int = false;
	// if(value == (int)value) is_int = true;

	switch (eval_type) {
		case TokenType::PLUS:
			return Number(this->value + value);
		case TokenType::MINUS:
			return Number(this->value - value);
		case TokenType::MUL:
			return Number(this->value * value);
		case TokenType::DIV:
			return Number(this->value / value);
		default:
			throw std::runtime_error("Invalid operator at Number::eval");
	}
}

void Number::set_pos(const Position pos) {
	this->pos = pos;
}




/* PRIVATE */
