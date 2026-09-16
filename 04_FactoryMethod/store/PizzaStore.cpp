#include "store/PizzaStore.h"

#include <iostream>

std::unique_ptr<Pizza> PizzaStore::orderPizza(const std::string& type) {
	std::unique_ptr<Pizza> pizza = createPizza(type);   // <-- 팩토리 메소드
	if (!pizza) {
		std::cout << "그런 피자는 없습니다: " << type << "\n\n";
		return nullptr;
	}
	pizza->prepare();
	pizza->bake();
	pizza->cut();
	pizza->box();
	std::cout << "-> " << pizza->getName() << " 완성\n\n";
	return pizza;
}
