#include "../headers/environment.hpp"

Environment::Environment() {}

template <template <typename> class Batype, typename T>
Batype<T> Environment::getVariable(const std::string& sym) const {
	// for(size_t i = 0; i < symbols.size(); ++i)
	// 	if (symbols[i] == sym)
	// 		return values[i];
	// return Variable {}; // Make new if not found

	auto it = symbols.find(sym);
	return (it != symbols.end()) ? it->second : Batype {}; // Make new if not find
}