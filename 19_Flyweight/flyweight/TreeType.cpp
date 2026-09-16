#include "flyweight/TreeType.h"

#include <iostream>
#include <utility>

TreeType::TreeType(std::string name, std::string color, std::string texture)
	: name_(std::move(name)), color_(std::move(color)), texture_(std::move(texture)) {}

void TreeType::draw(int x, int y, int age) const {
	std::cout << "  (" << x << ", " << y << ") " << name_ << " [" << color_ << "/" << texture_
	          << "] " << age << "년생\n";
}

const std::string& TreeType::name() const {
	return name_;
}
