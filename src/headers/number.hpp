#pragma once

#include "position.hpp"
#include "token.hpp"

#include <optional>

/**
 * This class creates a Number type
 *
 * Value is represented as double, but can have a type of INT or FLOAT, storing in double is just a simpler way of storing the value 
 * */


// I'm just using this instead of "BasicResult" because this would cause a circulatory
struct EvalResult {
	double value;
	std::optional<Error> error;

	EvalResult(const double value) : value(value) {}
	EvalResult(const Error& error) : error(error) {}

	bool has_error() {
		return error.has_value();
	}

	inline Error get_error() {
		return error.value();
	}

	inline double get_value() const {
		return value;
	}
};

class Number {
	public:
		Number(const double value);

		EvalResult eval(const double value, const TokenType eval_type, const Position& pos);

		inline Number set_pos(const Position pos) {
			this->pos = pos;
			return *this;
		}
	
		inline double get_value() const {
			return value;
		}

		inline Position get_pos() const {
			return pos.value();
		}

		inline std::string as_string() const {
			return Batring::num(value);
		}
	private:
		std::optional<Position> pos;
		double value;

		// Value value_num; // I don't how to call this, this is just to have a different name
};