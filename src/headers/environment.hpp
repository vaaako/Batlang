#pragma once

#include "batype.hpp"

#include <unordered_map>
#include <vector>
#include <string>


class Environment {
	public:
		Environment();

		template <template <typename> class Batype, typename T>
		inline void addVariable(const std::string& sym, const Batype<T>& val) {
			// symbols.push_back(sym);
			// values.push_back(val);

			symbols.insert({ sym, val });
		}

		// Obtém o valor associado a um símbolo
		template <template <typename> class Batype, typename T>
		Batype<T> getVariable(const std::string& sym) const;
	private:
		// std::vector<std::string> symbols; // Store names
		// std::vector<Variable> values; // Values

		// template <template <typename> class Batype, typename T>
		// std::unordered_map<std::string, Batype> symbols = {};
		std::unordered_map<std::string, double> symbols = {};
};
