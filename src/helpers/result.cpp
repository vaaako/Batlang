#include "../headers/result.hpp"



/* PResult */
PResult::PResult() {}

PResult PResult::registr(const PResult& res) {
	if(res.has_error())
		error = res.get_error();
	return res;
}

/* RTResult */
RTResult::RTResult() : Result<Batype>() {}

RTResult RTResult::registr(const RTResult& res) {
	if(res.has_error())
		error = res.get_error();
	return res;
}
