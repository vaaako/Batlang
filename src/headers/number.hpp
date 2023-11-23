#pragma once

#include "batype.hpp"
#include "context.hpp"
#include "position.hpp"
#include "result.hpp"
#include "token.hpp"

#include <optional>

/**
 * This class creates a Number type
 *
 * Number is a tempalte to number types, wich can be a type of INT or FLOAT,
 * 
 * This class is derived from "Batype" wich represents any type of "Batlang"
 * */


// I'm just using this instead of "BasicResult" because this would cause a circulatory
// struct EvalResult {
// 	double value;
// 	std::optional<Error> error;

// 	EvalResult(const double value) : value(value) {}
// 	EvalResult(const Error& error) : error(error) {}

// 	bool has_error() {
// 		return error.has_value();
// 	}

// 	inline Error get_error() {
// 		return error.value();
// 	}

// 	inline double get_value() const {
// 		return value;
// 	}
// };


class Integer;
class Floating;

class Number {
	public:
		// Make number
		static inline Integer make_number(const int value, const std::optional<Position>& pos = std::nullopt, const std::optional<Context>& context = std::nullopt) {	
			return Integer(value, pos, context);
		}

		static inline Floating make_number(const double value, const std::optional<Position>& pos = std::nullopt, const std::optional<Context>& context = std::nullopt) {
			return Floating(value, pos, context);
		}

		// It's dangerous to use "Batype" as a number paramter, so I need to be careful
		template <template <typename> class BasicType, typename T>
		static BasicResult<double> eval(const double value, const TokenType eval_type, const Number& num, const Position& pos);
};



class Integer : public BaseType<int>, public Number {
	public:
		Integer(const int value, const std::optional<Position>& pos, const std::optional<Context>& context);
		
		inline std::string as_string() const override {
			return Batring::num(this->get_value());
		}

		inline BasicResult<double> eval(const double value, const TokenType eval_type, const Position& pos) const {
			return Number::eval(value, eval_type, this, pos);
		}
};

class Floating : public BaseType<double>, public Number {
	public:
		Floating(const double value, const std::optional<Position>& pos, const std::optional<Context>& context);
		
		inline std::string as_string() const override {
			return Batring::num(this->get_value());
		}

		inline BasicResult<double> eval(const double value, const TokenType eval_type, const Position& pos) const {

		}
};

/* Number types */

