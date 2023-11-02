#pragma once

#include "position.hpp"
#include "token.hpp"
#include <optional>

/**
 * - Just "number" type for now
 * */

class Number {
	public:
		Number(double value);

		Number* eval(double value, TokenType eval_type);

		Number* set_pos(Position pos);
	
		inline double get_value() {
			return value;
		}

		inline std::string as_string() {
			return Batring::num(value);
		}
	private:
		std::optional<Position> pos;
		double value;

		// Value value_num; // I don't how to call this, this is just to have a different name
};