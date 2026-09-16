#ifndef NY_N_Y_PIZZA_STORE_H
#define NY_N_Y_PIZZA_STORE_H

#include <memory>
#include <string>

#include "store/PizzaStore.h"

// ConcreteCreator : 뉴욕 지점. 만드는 물건만 다르고 주문 흐름은 물려받는다.
class NYPizzaStore : public PizzaStore {
protected:
	std::unique_ptr<Pizza> createPizza(const std::string& type) override;
};

#endif
