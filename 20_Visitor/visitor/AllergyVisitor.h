#ifndef VISITOR_ALLERGY_VISITOR_H
#define VISITOR_ALLERGY_VISITOR_H

#include <string>

#include "element/Ingredient.h"
#include "element/Menu.h"
#include "element/MenuItem.h"
#include "visitor/Visitor.h"

// ConcreteVisitor 3 : 알레르기 검사 (또 추가해도 구조는 그대로)
class AllergyVisitor : public Visitor {
public:
	explicit AllergyVisitor(std::string allergen);

	void visit(const MenuItem& item) override;
	void visit(const Menu&) override;
	void visit(const Ingredient& ing) override;

private:
	std::string allergen_;
	std::string current_;
};

#endif
