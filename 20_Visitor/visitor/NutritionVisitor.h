#ifndef VISITOR_NUTRITION_VISITOR_H
#define VISITOR_NUTRITION_VISITOR_H

#include "element/Ingredient.h"
#include "element/Menu.h"
#include "element/MenuItem.h"
#include "visitor/Visitor.h"

// ConcreteVisitor 1 : 영양 정보 합산
class NutritionVisitor : public Visitor {
public:
	void visit(const MenuItem& item) override;
	void visit(const Menu& menu) override;
	void visit(const Ingredient& ing) override;

	void printTotal() const;

private:
	int calories_ = 0;
	int protein_ = 0;
	int carbs_ = 0;
};

#endif
