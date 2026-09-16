#include "element/Menu.h"

#include <utility>

Menu::Menu(std::string name) : name_(std::move(name)) {}

void Menu::add(std::shared_ptr<MenuComponent> c) {
	children_.push_back(std::move(c));
}

const std::string& Menu::name() const {
	return name_;
}

void Menu::accept(Visitor& v) const {
	v.visit(*this);
	for (const auto& c : children_) c->accept(v);
}
