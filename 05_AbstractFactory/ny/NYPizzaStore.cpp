#include "ny/NYPizzaStore.h"

#include "pizza/CheesePizza.h"
#include "pizza/ClamPizza.h"

std::unique_ptr<Pizza> NYPizzaStore::createPizza(const std::string& type) {
	std::unique_ptr<Pizza> p;
	if (type == "cheese") {
		p = std::make_unique<CheesePizza>(factory_);
		p->setName("뉴욕 스타일 치즈 피자");
	} else if (type == "clam") {
		p = std::make_unique<ClamPizza>(factory_);
		p->setName("뉴욕 스타일 조개 피자");
	}
	return p;
}
