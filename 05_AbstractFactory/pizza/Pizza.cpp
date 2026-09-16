#include "pizza/Pizza.h"

#include <iostream>
#include <utility>

Pizza::Pizza(const PizzaIngredientFactory& f) : factory_(f) {}

void Pizza::bake() const {
	std::cout << "  175도에서 25분 간 굽기\n";
}

void Pizza::cut() const {
	std::cout << "  피자를 부채꼴 모양으로 자르기\n";
}

void Pizza::box() const {
	std::cout << "  피자를 상자에 담기\n";
}

void Pizza::setName(std::string n) {
	name_ = std::move(n);
}

const std::string& Pizza::getName() const {
	return name_;
}
