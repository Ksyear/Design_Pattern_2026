#include "condiment/Soy.h"

std::string Soy::getDescription() const {
	return beverage_->getDescription() + ", 두유";
}

double Soy::cost() const {
	double extra = 0.10;
	switch (getSize()) {
		case Size::Tall:   extra = 0.10; break;
		case Size::Grande: extra = 0.15; break;
		case Size::Venti:  extra = 0.20; break;
	}
	return beverage_->cost() + extra;
}
