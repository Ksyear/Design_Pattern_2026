#include "chicago/ChicagoPizzaStore.h"

#include "chicago/ChicagoStyleCheesePizza.h"
#include "chicago/ChicagoStyleClamPizza.h"

std::unique_ptr<Pizza> ChicagoPizzaStore::createPizza(const std::string& type) {
	if (type == "cheese") return std::make_unique<ChicagoStyleCheesePizza>();
	if (type == "clam")   return std::make_unique<ChicagoStyleClamPizza>();
	return nullptr;
}
