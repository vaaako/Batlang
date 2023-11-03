#pragma once

#include "error.hpp"
#include "nodes.hpp"

#include <optional>

class Result {
	public:
		Result();

		Result registr(Result res); // Register
		Result sucess(Node* node);
		Result failure(Error error);
		

		inline bool has_error() const {
			return (error.has_value()) ? true : false;
		}

		inline std::optional<Error> get_error() const {
			return error;
		}

		inline Node* get_node() {
			return node;
		}
	private:
		std::optional<Error> error;
		Node* node;	
};

class RTResult {
	public:
		RTResult();

		RTResult registr(RTResult res);
		RTResult sucess(double value);
		RTResult failure(Error error);

		inline bool has_error() const {
			return (error.has_value()) ? true : false;
		}

		inline std::optional<Error> get_error() const {
			return error;
		}

		inline double get_value() {
			return value;
		}
	private:
		std::optional<Error> error;
		double value;
};