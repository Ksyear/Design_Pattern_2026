#include "beverage/CoffeeWithHook.h"

#include <iostream>

CoffeeWithHook::CoffeeWithHook(bool wantsCondiments) : wants_(wantsCondiments) {}

bool CoffeeWithHook::customerWantsCondiments() const {
	std::cout << "  (손님에게 물어봄: 우유와 설탕을 넣을까요? -> "
	          << (wants_ ? "예" : "아니오") << ")\n";
	return wants_;
}
