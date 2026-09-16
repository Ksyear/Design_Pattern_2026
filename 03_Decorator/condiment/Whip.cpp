#include "condiment/Whip.h"

std::string Whip::getDescription() const {
	return beverage_->getDescription() + ", 휘핑크림";
}

double Whip::cost() const {
	return beverage_->cost() + 0.10;
}
