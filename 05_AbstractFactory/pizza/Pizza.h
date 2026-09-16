#ifndef PIZZA_PIZZA_H
#define PIZZA_PIZZA_H

#include <memory>
#include <string>

#include "factory/PizzaIngredientFactory.h"
#include "ingredient/Cheese.h"
#include "ingredient/Clams.h"
#include "ingredient/Dough.h"
#include "ingredient/Sauce.h"

// Client
// Pizza 는 이제 구상 재료를 전혀 모른다. 공장 인터페이스에만 의존한다 (DIP).
class Pizza {
public:
	explicit Pizza(const PizzaIngredientFactory& f);
	virtual ~Pizza() = default;

	virtual void prepare() = 0;

	void bake() const;
	void cut() const;
	void box() const;

	void setName(std::string n);
	const std::string& getName() const;

protected:
	const PizzaIngredientFactory& factory_;
	std::string name_;
	std::unique_ptr<Dough> dough_;
	std::unique_ptr<Sauce> sauce_;
	std::unique_ptr<Cheese> cheese_;
	std::unique_ptr<Clams> clam_;
};

#endif
