#include "ny/NYPizzaStore.h"

#include "ny/NYStyleCheesePizza.h"
#include "ny/NYStyleClamPizza.h"

std::unique_ptr<Pizza> NYPizzaStore::createPizza(const std::string& type) {
	if (type == "cheese") return std::make_unique<NYStyleCheesePizza>();
	if (type == "clam")   return std::make_unique<NYStyleClamPizza>();
	return nullptr;
}
