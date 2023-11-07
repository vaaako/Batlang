#include "../headers/context.hpp"

Context::Context(const std::string name, const Position parent_entry_pos, Context* parent) : name(name), parent_entry_pos(parent_entry_pos), parent(parent) {}
Context::Context(const std::string name) : name(name), parent(nullptr) {}
