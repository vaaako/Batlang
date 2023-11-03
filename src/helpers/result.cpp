#include "../headers/result.hpp"

template <typename T>
Result<T>::Result() {}

/* PResult */
PResult::PResult() {}

PResult PResult::registr(PResult res) {
	if(res.has_error())
		error = std::move(res.get_error().value());
	return res;
}

/* RTResult */
RTResult::RTResult() {}

RTResult RTResult::registr(RTResult res) {
	if(res.has_error())
		error = std::move(res.get_error().value());
	return res;
}
