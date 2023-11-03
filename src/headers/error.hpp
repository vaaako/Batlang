#pragma once

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
		// Error(Position pos, Position pos_end, std::string name, std::string detail);
		Error(const ErrorType error_type, const Position pos, const std::string detail);
		Error(const ErrorType error_type, const std::string detail);

		inline std::string get_name() const {
			return name;
		}

		inline std::string get_detail() const {
			return detail;
		}

		inline Position get_pos() const {
			return pos;
		}

	private:
		Position pos;
		std::string name;
		std::string detail;

		std::unordered_map<ErrorType, std::string> error_hash = {
			{ ErrorType::IllegalCharError,   "Illegal Character"  },
			{ ErrorType::InvalidSyntaxError, "Invalid Syntax" },
			{ ErrorType::RuntimeError,       "Runtime Error" },
		};
};
