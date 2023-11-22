#include "../headers/batype.hpp"

Batype::Batype(const std::optional<Position>& pos, const std::optional<Context>& context) {}

template <typename T>
BaseType<T>::BaseType(const T value, const std::optional<Position>& pos, const std::optional<Context>& context) : value(value), Batype(pos, context) {};
