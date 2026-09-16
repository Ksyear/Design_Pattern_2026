#include "ny/NYPizzaIngredientFactory.h"

#include "ny/FreshClams.h"
#include "ny/MarinaraSauce.h"
#include "ny/ReggianoCheese.h"
#include "ny/ThinCrustDough.h"

std::unique_ptr<Dough> NYPizzaIngredientFactory::createDough() const {
	return std::make_unique<ThinCrustDough>();
}

std::unique_ptr<Sauce> NYPizzaIngredientFactory::createSauce() const {
	return std::make_unique<MarinaraSauce>();
}

std::unique_ptr<Cheese> NYPizzaIngredientFactory::createCheese() const {
	return std::make_unique<ReggianoCheese>();
}

std::unique_ptr<Clams> NYPizzaIngredientFactory::createClam() const {
	return std::make_unique<FreshClams>();
}
