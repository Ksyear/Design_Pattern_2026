#ifndef VISITOR_HEALTH_RATING_VISITOR_H
#define VISITOR_HEALTH_RATING_VISITOR_H

#include <string>

#include "element/Ingredient.h"
#include "element/Menu.h"
#include "element/MenuItem.h"
#include "visitor/Visitor.h"

// ConcreteVisitor 2 : 기존 구조를 하나도 안 건드리고 기능 추가
class HealthRatingVisitor : public Visitor {
public:
	void visit(const MenuItem& item) override;
	void visit(const Menu&) override;
	void visit(const Ingredient& ing) override;

	void finish();

private:
	void report() const;

	std::string currentName_;
	int currentCalories_ = 0;
};

#endif
