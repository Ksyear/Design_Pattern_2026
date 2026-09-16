#include "visitor/HealthRatingVisitor.h"

#include <iomanip>
#include <iostream>

void HealthRatingVisitor::visit(const MenuItem& item) {
	if (currentCalories_ > 0) report();
	currentName_ = item.name();
	currentCalories_ = 0;
}

void HealthRatingVisitor::visit(const Menu&) {}

void HealthRatingVisitor::visit(const Ingredient& ing) {
	currentCalories_ += ing.calories();
}

void HealthRatingVisitor::finish() {
	if (currentCalories_ > 0) report();
}

void HealthRatingVisitor::report() const {
	const char* rating = currentCalories_ < 300 ? "A (가벼움)"
	                    : currentCalories_ < 600 ? "B (보통)"
	                                             : "C (든든함)";
	std::cout << "  " << std::left << std::setw(20) << currentName_ << currentCalories_
	          << "kcal -> " << rating << '\n';
}
