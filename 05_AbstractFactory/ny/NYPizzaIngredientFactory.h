#ifndef NY_N_Y_PIZZA_INGREDIENT_FACTORY_H
#define NY_N_Y_PIZZA_INGREDIENT_FACTORY_H

#include <memory>

#include "factory/PizzaIngredientFactory.h"

// Concrete Factory : 변종(variant) 하나당 공장 하나.
// 이 폴더 안의 재료만 만들기 때문에 재료가 서로 어긋날 수가 없다.
class NYPizzaIngredientFactory : public PizzaIngredientFactory {
public:
	std::unique_ptr<Dough>  createDough() const override;
	std::unique_ptr<Sauce>  createSauce() const override;
	std::unique_ptr<Cheese> createCheese() const override;
	std::unique_ptr<Clams>  createClam() const override;
};

#endif
