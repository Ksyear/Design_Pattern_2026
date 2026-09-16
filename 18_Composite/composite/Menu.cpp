#include "composite/Menu.h"

#include <iostream>
#include <utility>

Menu::Menu(std::string name, std::string description)
	: name_(std::move(name)), description_(std::move(description)) {}

void Menu::add(std::shared_ptr<MenuComponent> c) {
	children_.push_back(std::move(c));
}

void Menu::remove(const std::shared_ptr<MenuComponent>& c) {
	for (auto it = children_.begin(); it != children_.end(); ++it) {
		if (*it == c) { children_.erase(it); return; }
	}
}

const std::string& Menu::getName() const {
	return name_;
}

const std::string& Menu::getDescription() const {
	return description_;
}

void Menu::print(int depth) const {
	std::cout << '\n' << indent(depth) << name_ << ", " << description_ << '\n';
	std::cout << indent(depth) << std::string(30, '-') << '\n';
	for (const auto& child : children_) child->print(depth + 1);
}

double Menu::totalPrice() const {
	double sum = 0.0;
	for (const auto& child : children_) {
		if (auto* sub = dynamic_cast<const Menu*>(child.get())) sum += sub->totalPrice();
		else sum += child->getPrice();
	}
	return sum;
}
