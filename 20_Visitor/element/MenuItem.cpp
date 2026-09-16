#include "element/MenuItem.h"

#include <utility>

MenuItem::MenuItem(std::string name, std::vector<Ingredient> ingredients)
	: name_(std::move(name)), ingredients_(std::move(ingredients)) {}

const std::string& MenuItem::name() const {
	return name_;
}

const std::vector<Ingredient>& MenuItem::ingredients() const {
	return ingredients_;
}

void MenuItem::accept(Visitor& v) const {
	v.visit(*this);
	for (const auto& ing : ingredients_) ing.accept(v);
}
