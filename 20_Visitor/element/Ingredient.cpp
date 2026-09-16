#include "element/Ingredient.h"

#include <utility>

Ingredient::Ingredient(std::string name, int calories, int protein, int carbs)
	: name_(std::move(name)), calories_(calories), protein_(protein), carbs_(carbs) {}

const std::string& Ingredient::name() const {
	return name_;
}

int Ingredient::calories() const {
	return calories_;
}

int Ingredient::protein() const {
	return protein_;
}

int Ingredient::carbs() const {
	return carbs_;
}

void Ingredient::accept(Visitor& v) const {
	v.visit(*this);
}
