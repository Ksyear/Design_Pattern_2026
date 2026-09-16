#include "store/PizzaStore.h"

#include <iostream>

void PizzaStore::orderPizza(const std::string& type) {
	auto pizza = createPizza(type);
	if (!pizza) { std::cout << "그런 피자는 없습니다\n\n"; return; }
	pizza->prepare();
	pizza->bake();
	pizza->cut();
	pizza->box();
	std::cout << "-> " << pizza->getName() << " 완성\n\n";
}
