#pragma once

#include "error.hpp"
#include "nodes.hpp"
#include "number.hpp"
#include "token.hpp"

#include <optional>

/**
 * This class is used to handle errors in Parser and Interpreter
 * In registr (register is a C++ keyword, so i can't use this name)
 * Is registered a result (or answer) of a action, if the answer had a error, this error is also registered (failure)
 * 
 * Then in the code is check if the Result has a error, if has, cancel and show this error
 * But, if no errors occured, return result with the value (sucess)
 * */

template <typename T>
class BasicResult {
	public:
		BasicResult(const T value, const Error error) : value(value), error(error) {} // In case default "value" can't be 0
		BasicResult(const T value) : value(value) {}
		BasicResult(const Error error) : value(0), error(error) {}

		inline bool has_error() const {
			return error.has_value();
		}

		inline Error get_error() const {
			return error.value();
		}

		inline T get_value() const {
			return value;
		}
	private:
		T value;
		std::optional<Error> error;
};


template <typename T>
class Result {
	public:
		Result() {}
		Result(T value) : value(value) {}

		// Register
		Result<T> registr(Result<T> res);
	
		// Register
		void sucess(T value) {
			this->value = value;
		}

		void failure(Error error) {
			this->error = error;
		}
		

		inline bool has_error() const {
			return (error.has_value()) ? true : false;
		}

		inline Error get_error() const {
			return error.value();
		}

		inline T get_value() const {
			return value;
		}

	protected:
		std::optional<Error> error;
		T value;
};


// Parser Result
class PResult : public Result<Node*> {
	public:
		PResult();

		// I have to do this in each child because it have to accept only itself
		PResult registr(PResult res);
	private:
};

// Runtime Result (interpreter)
class RTResult : public Result<Number> {
	public:
		RTResult();

		RTResult registr(RTResult res);
	private:
};