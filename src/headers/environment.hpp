#pragma once

#include "batype.hpp"

#include <unordered_map>
#include <vector>
#include <string>


class Environment {
	public:
		Environment();

		inline void addVariable(const std::string& sym, const Batype& val) {
			// symbols.push_back(sym);
			// values.push_back(val);

			symbols.insert({ sym, val });
		}

		// Obtém o valor associado a um símbolo
		// template <template <typename> class Batype, typename T>
		Batype getVariable(const std::string& sym) const;
	private:
		// std::vector<std::string> symbols; // Store names
		// std::vector<Variable> values; // Values

		std::unordered_map<std::string, Batype> symbols = {};
};
