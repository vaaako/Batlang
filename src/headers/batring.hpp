#include "value.hpp"
#include <sstream>
#include <string>
#include <iomanip>

// Convert types to string
class Batring {
	public:
		static std::string num(double value);
		static std::string result(std::string value);
	private:
		static std::string fix_float(double value) {
			std::stringstream ss;
			ss << std::fixed << value;
			std::string result = ss.str();

			// Remove trailing zeros
			while(!result.empty() && (result.back() == '0' || result.back() == '.')) {
				result.pop_back();
			}
			return result;
		}
};