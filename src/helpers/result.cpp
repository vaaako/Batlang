#include "../headers/result.hpp"



/* PResult */
PResult::PResult() {}

PResult PResult::registr(PResult res) {
	if(res.has_error())
		error = res.get_error();
	return res;
}

/* RTResult */
RTResult::RTResult() : Result<Number>(0) {}

RTResult RTResult::registr(RTResult res) {
	if(res.has_error())
		error = res.get_error();
	return res;
}
