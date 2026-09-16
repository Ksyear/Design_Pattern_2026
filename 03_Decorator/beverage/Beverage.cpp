#include "beverage/Beverage.h"

#include <utility>

Beverage::Beverage(std::string description) : description_(std::move(description)) {}

std::string Beverage::getDescription() const {
	return description_;
}

void Beverage::setSize(Size s) {
	size_ = s;
}

Beverage::Size Beverage::getSize() const {
	return size_;
}
