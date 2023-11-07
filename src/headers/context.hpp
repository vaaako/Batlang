#pragma once

#include "position.hpp"

#include <memory>
#include <optional>
#include <string>

/**
 * This class is used to know where a Error came from
 * If was from inside a class, function, file etc. 
 * It is passed in Error constructor, but is optional 
 * */

class Context {
	public:
		Context(const std::string name, const Position parent_entry_pos, Context* parent=nullptr);
		Context(const std::string name);

		inline std::string get_name() {
			return name;
		}

		inline Position get_pos() {
			return parent_entry_pos.value();
		}

		inline Context get_parent() {
			return *parent;
		}

		inline bool has_parent() {
			return parent != nullptr;
		}


		~Context() {
			delete parent;
		}
	private:
		std::string name;
		std::optional<Position> parent_entry_pos;
		Context* parent;
};