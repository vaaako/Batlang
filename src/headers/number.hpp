#pragma once

#include "batype.hpp"
#include "context.hpp"
#include "position.hpp"
#include "token.hpp"

#include <optional>

/**
 * This class creates a Number type
 *
 * Value is represented as double, but can have a type of INT or FLOAT,
 * storing in double is just a simpler way of storing the value 
 * 
 * This class is derived from "Batype" wich represents any type of "Batlang"
 * 
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

// class Integer : public Batype<int> {
// 	public:
// 		Integer(const int value) : Batype<int>(value) {};
// };

class Number : public Batype<double> {
	public:
		// Number(const double value) : Batype<double>(value) {};
		// Number(const double value, const Position& pos) : Batype<double>(value, pos) {};
		// Number(const double value, const Context& context) : Batype<double>(value, context) {};
		// Number(const double value, const Position& pos, const Context& context) : Batype<double>(value, pos, context) {};

		Number(const double value, const std::optional<Position>& pos, const std::optional<Context>& context) : Batype<double>(value, pos, context) {};


		EvalResult eval(const double value, const TokenType eval_type, const Position& pos);

		inline double get_value() const {
			return value;
		}

		inline Position get_pos() const {
			return pos.value();
		}

		inline void set_pos(const Position pos) {
			this->pos = pos;
		}	

		inline void set_context(const Context& context) {
			this->context = context;
		}

		inline std::string as_string() const {
			return Batring::num(value);
		}
	private:
		double value;
		std::optional<Position> pos;
		std::optional<Context> context;

		// Value value_num; // I don't how to call this, this is just to have a different name
};