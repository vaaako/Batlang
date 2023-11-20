#pragma once

#include "context.hpp"
#include "position.hpp"

template <typename T>
class Batype {
	public:
		// Batype<T>(const T value) : value(value) {};
		// Batype<T>(const T value, const Position& pos) : value(value), pos(pos) {};
		// Batype<T>(const T value, const Context& context) : value(value), context(context) {};
		// Batype<T>(const T value, const Position& pos, const Context& context) : value(value), pos(pos), context(context) {};

		Batype<T>(const T value, const std::optional<Position>& pos, const std::optional<Context>& context) : value(value), pos(pos), context(context) {};

		inline T get_value() const {
			return value;
		}

		inline Position get_pos() const {
			return pos.value();
		}

		inline void set_pos(const Position pos) {
			this->pos = pos;
		}

		inline void set_context(const Context& context) {
			this->context = context;
		}

		// virtual inline std::string as_string() = 0;

		virtual ~Batype() = default;
	private:
		T value;
		std::optional<Position> pos;
		std::optional<Context> context;
};