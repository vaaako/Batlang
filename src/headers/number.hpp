#pragma once

#include "position.hpp"
#include "token.hpp"
#include <optional>

/**
 * - Just "number" type for now
 * */

class Number {
	public:
		Number(const double value);

		Number* eval(const double value, const TokenType eval_type);

		Number* set_pos(const Position pos);
	
		inline double get_value() const {
			return value;
		}

		inline std::string as_string() const {
			return Batring::num(value);
		}
	private:
		std::optional<Position> pos;
		double value;

		// Value value_num; // I don't how to call this, this is just to have a different name
};