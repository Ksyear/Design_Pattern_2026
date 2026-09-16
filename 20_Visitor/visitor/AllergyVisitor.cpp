#include "visitor/AllergyVisitor.h"

#include <iostream>
#include <utility>

AllergyVisitor::AllergyVisitor(std::string allergen) : allergen_(std::move(allergen)) {}

void AllergyVisitor::visit(const MenuItem& item) {
	current_ = item.name();
}

void AllergyVisitor::visit(const Menu&) {}

void AllergyVisitor::visit(const Ingredient& ing) {
	if (ing.name().find(allergen_) != std::string::npos) {
		std::cout << "  경고: " << current_ << " 에 '" << allergen_ << "' 포함 (" << ing.name()
		          << ")\n";
	}
}
