#include "condiment/CondimentDecorator.h"

#include <utility>

CondimentDecorator::CondimentDecorator(std::unique_ptr<Beverage> b)
	: beverage_(std::move(b)) {}

void CondimentDecorator::setSize(Size s) {
	beverage_->setSize(s);
}

Beverage::Size CondimentDecorator::getSize() const {
	return beverage_->getSize();
}
