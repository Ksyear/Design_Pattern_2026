#include "chicago/ChicagoPizzaIngredientFactory.h"

#include "chicago/FrozenClams.h"
#include "chicago/MozzarellaCheese.h"
#include "chicago/PlumTomatoSauce.h"
#include "chicago/ThickCrustDough.h"

std::unique_ptr<Dough> ChicagoPizzaIngredientFactory::createDough() const {
	return std::make_unique<ThickCrustDough>();
}

std::unique_ptr<Sauce> ChicagoPizzaIngredientFactory::createSauce() const {
	return std::make_unique<PlumTomatoSauce>();
}

std::unique_ptr<Cheese> ChicagoPizzaIngredientFactory::createCheese() const {
	return std::make_unique<MozzarellaCheese>();
}

std::unique_ptr<Clams> ChicagoPizzaIngredientFactory::createClam() const {
	return std::make_unique<FrozenClams>();
}
