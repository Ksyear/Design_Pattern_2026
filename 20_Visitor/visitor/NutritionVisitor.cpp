#include "visitor/NutritionVisitor.h"

#include <iostream>

void NutritionVisitor::visit(const MenuItem& item) {
	std::cout << "  [메뉴] " << item.name() << '\n';
}

void NutritionVisitor::visit(const Menu& menu) {
	std::cout << "[" << menu.name() << "]\n";
}

void NutritionVisitor::visit(const Ingredient& ing) {
	calories_ += ing.calories();
	protein_ += ing.protein();
	carbs_ += ing.carbs();
	std::cout << "    - " << ing.name() << " (" << ing.calories() << "kcal)\n";
}

void NutritionVisitor::printTotal() const {
	std::cout << "\n  합계: " << calories_ << "kcal, 단백질 " << protein_ << "g, 탄수화물 "
	          << carbs_ << "g\n";
}
