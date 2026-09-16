#include "leaf/MenuItem.h"

#include <iomanip>
#include <iostream>
#include <utility>

MenuItem::MenuItem(std::string name, std::string description, bool vegetarian, double price)
	: name_(std::move(name)), description_(std::move(description)), vegetarian_(vegetarian),
	  price_(price) {}

const std::string& MenuItem::getName() const {
	return name_;
}

const std::string& MenuItem::getDescription() const {
	return description_;
}

double MenuItem::getPrice() const {
	return price_;
}

bool MenuItem::isVegetarian() const {
	return vegetarian_;
}

void MenuItem::print(int depth) const {
	std::cout << indent(depth) << "  " << name_;
	if (vegetarian_) std::cout << " (v)";
	std::cout << ", $" << std::fixed << std::setprecision(2) << price_ << std::defaultfloat
	          << "\n" << indent(depth) << "     -- " << description_ << '\n';
}
