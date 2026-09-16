#include "pizza/Pizza.h"

#include <iostream>
#include <utility>

Pizza::Pizza(std::string name, std::vector<std::string> toppings)
	: name_(std::move(name)), toppings_(std::move(toppings)) {}

void Pizza::prepare() const {
	std::cout << "준비 중: " << name_ << '\n';
	std::cout << "  도우를 돌리는 중...\n";
	std::cout << "  소스를 뿌리는 중...\n";
	std::cout << "  토핑을 올리는 중: ";
	for (const auto& t : toppings_) std::cout << t << ' ';
	std::cout << '\n';
}

void Pizza::bake() const {
	std::cout << "  175도에서 25분 간 굽기\n";
}

void Pizza::cut() const {
	std::cout << "  피자를 부채꼴 모양으로 자르기\n";
}

void Pizza::box() const {
	std::cout << "  피자를 상자에 담기\n";
}

const std::string& Pizza::getName() const {
	return name_;
}
