#pragma once

struct Value {
	double value;
	bool is_int;

	Value(double value, bool is_int=false) : value(value), is_int(is_int) {}
};