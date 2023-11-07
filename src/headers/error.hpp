#pragma once

#include "context.hpp"
#include "position.hpp"

#include <string>
#include <unordered_map>

enum class ErrorType {
	IllegalCharError,
	InvalidSyntaxError,
	RuntimeError
};



class Error {
	public:
		Error(const ErrorType error_type, const std::string detail, const Position& pos, const Context& context);
		Error(const ErrorType error_type, const std::string detail, const Position& pos);

		inline std::string get_name() const {
			return name;
		}

		inline std::string get_detail() const {
			return detail;
		}

		inline Position get_pos() const {
			return pos;
		}

		inline Context get_context() const {
			return context.value();
		}

		inline bool has_context() const {
			return context.has_value();
		}

	private:
		std::string detail;
		Position pos;
		std::optional<Context> context;
		std::string name;


		std::unordered_map<ErrorType, std::string> error_hash = {
			{ ErrorType::IllegalCharError,   "Illegal Character"  },
			{ ErrorType::InvalidSyntaxError, "Invalid Syntax" },
			{ ErrorType::RuntimeError,       "Runtime Error" },
		};
};
