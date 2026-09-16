#ifndef CHICAGO_CHICAGO_PIZZA_STORE_H
#define CHICAGO_CHICAGO_PIZZA_STORE_H

#include <memory>
#include <string>

#include "chicago/ChicagoPizzaIngredientFactory.h"
#include "store/PizzaStore.h"

// 팩토리 메소드(createPizza)와 추상 팩토리(factory_)를 함께 쓰는 자리.
// 어떤 제품군을 쓸지는 이 지점이 고르고, Pizza 는 그 선택을 모른다.
class ChicagoPizzaStore : public PizzaStore {
protected:
	std::unique_ptr<Pizza> createPizza(const std::string& type) override;

private:
	ChicagoPizzaIngredientFactory factory_;
};

#endif
