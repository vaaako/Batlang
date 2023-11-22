#include "../headers/number.hpp"
#include "../headers/error.hpp"

#include <cmath>
#include <stdexcept>

Number::Integer::Integer(const int value, const std::optional<Position>& pos, const std::optional<Context>& context) : BaseType<int>(value, pos, context) {}
Number::Floating::Floating(const double value, const std::optional<Position>& pos, const std::optional<Context>& context) : BaseType<double>(value, pos, context) {}


template <template <typename> class BasicType, typename T>
BasicResult<double> Number::eval(const double value, const TokenType eval_type, const BasicType<T>* num, const Position& pos) {
	double result;
	double num_value = num->get_value();

	switch (eval_type) {
		case TokenType::PLUS:
			result = value + num_value;
			break;
		case TokenType::MINUS:
			result = value - num_value;
			break;
		case TokenType::MUL:
			result = value * num_value;
			break;
		case TokenType::DIV:
			// This is just a test, after I will return as NAN
			if(value == 0 && num_value == 0) return BasicResult<double>(0, Error(ErrorType::RuntimeError, "Division by 0", pos, num->get_context()) );

			result = value / num_value;
			break;
		case TokenType::POW:
			result = std::pow(value, num_value);
			break;
		default:
			throw std::runtime_error("<number.cpp> Invalid operator");
	}


	return BasicResult<double>(result);
}


/* PRIVATE */
