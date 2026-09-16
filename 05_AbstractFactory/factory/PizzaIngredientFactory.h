#ifndef FACTORY_PIZZA_INGREDIENT_FACTORY_H
#define FACTORY_PIZZA_INGREDIENT_FACTORY_H

#include <memory>

#include "ingredient/Cheese.h"
#include "ingredient/Clams.h"
#include "ingredient/Dough.h"
#include "ingredient/Sauce.h"

// Abstract Factory
//
// 핵심: 팩토리 메소드가 '제품 하나'를 만든다면, 추상 팩토리는 '제품군(family)'을 만든다.
//       한 공장에서 뽑은 재료끼리는 반드시 어울린다는 점이 보장된다.
//
// 관계: 추상 팩토리의 각 생성 메소드는 대개 팩토리 메소드로 구현된다.
class PizzaIngredientFactory {
public:
	virtual ~PizzaIngredientFactory() = default;
	virtual std::unique_ptr<Dough>  createDough() const = 0;
	virtual std::unique_ptr<Sauce>  createSauce() const = 0;
	virtual std::unique_ptr<Cheese> createCheese() const = 0;
	virtual std::unique_ptr<Clams>  createClam() const = 0;
};

#endif
