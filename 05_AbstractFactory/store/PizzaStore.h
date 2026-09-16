#ifndef STORE_PIZZA_STORE_H
#define STORE_PIZZA_STORE_H

#include <memory>
#include <string>

#include "pizza/Pizza.h"

// Creator : 주문 흐름은 고정, 무엇을 만들지만 서브클래스가 정한다
class PizzaStore {
public:
	virtual ~PizzaStore() = default;
	void orderPizza(const std::string& type);

protected:
	virtual std::unique_ptr<Pizza> createPizza(const std::string& type) = 0;
};

#endif
