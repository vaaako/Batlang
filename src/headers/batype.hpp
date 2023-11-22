#pragma once

#include "context.hpp"
#include "position.hpp"
#include <optional>

/**
 * "Batype" is any Batlang type
 * 
 * BaseType is used just to make a type, Batype is used as a
 * "reference" (not a C/C++ way) to this type, to be easier to use
 * */

// Use it
class Batype {
	public:
		Batype(const std::optional<Position>& pos = std::nullopt, const std::optional<Context>& context = std::nullopt);

		inline Position get_pos() const {
			return pos.value();
		}

		inline Context get_context() const {
			return context.value();
		}

		inline void set_pos(const Position pos) {
			this->pos = pos;
		}

		inline void set_context(const Context& context) {
			this->context = context;
		}

		// virtual std::string as_string() = 0;
	private:
		std::optional<Position> pos;
		std::optional<Context> context;
};

// Value only (This is just to set the value, it may have a better way to do it)
template <typename T>
class BaseType : public Batype {
	public:
		BaseType<T>(const T value, const std::optional<Position>& pos, const std::optional<Context>& context);

		inline T get_value() const {
			return value;
		}

		virtual ~BaseType() = default;
		virtual std::string as_string() const = 0;
	private:
		T value;
};
