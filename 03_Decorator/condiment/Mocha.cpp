#include "condiment/Mocha.h"

std::string Mocha::getDescription() const {
	return beverage_->getDescription() + ", 모카";
}

double Mocha::cost() const {
	return beverage_->cost() + 0.20;
}
