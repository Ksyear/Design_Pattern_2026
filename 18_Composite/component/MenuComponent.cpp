#include "component/MenuComponent.h"

#include <cstddef>
#include <stdexcept>

void MenuComponent::add(std::shared_ptr<MenuComponent>) {
	throw std::logic_error("지원하지 않는 연산");
}

void MenuComponent::remove(const std::shared_ptr<MenuComponent>&) {
	throw std::logic_error("지원하지 않는 연산");
}

const std::string& MenuComponent::getName() const {
	throw std::logic_error("지원하지 않는 연산");
}

const std::string& MenuComponent::getDescription() const {
	throw std::logic_error("지원하지 않는 연산");
}

double MenuComponent::getPrice() const {
	throw std::logic_error("지원하지 않는 연산");
}

bool MenuComponent::isVegetarian() const {
	throw std::logic_error("지원하지 않는 연산");
}

std::string MenuComponent::indent(int depth) {
	return std::string(static_cast<std::size_t>(depth) * 2, ' ');
}
