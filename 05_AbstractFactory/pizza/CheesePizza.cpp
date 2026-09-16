#include "pizza/CheesePizza.h"

#include <iostream>

void CheesePizza::prepare() {
	std::cout << "준비 중: " << name_ << '\n';
	dough_ = factory_.createDough();
	sauce_ = factory_.createSauce();
	cheese_ = factory_.createCheese();
	std::cout << "  " << dough_->name() << " / " << sauce_->name() << " / " << cheese_->name() << '\n';
}
