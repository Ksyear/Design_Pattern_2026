#include "beverage/CaffeineBeverage.h"

#include <iostream>

void CaffeineBeverage::prepareRecipe() {
	boilWater();
	brew();
	pourInCup();
	if (customerWantsCondiments()) {   // <-- 후크가 알고리즘의 흐름을 바꾼다
		addCondiments();
	}
	std::cout << '\n';
}

void CaffeineBeverage::boilWater() const {
	std::cout << "  물을 끓이는 중\n";
}

void CaffeineBeverage::pourInCup() const {
	std::cout << "  컵에 따르는 중\n";
}

bool CaffeineBeverage::customerWantsCondiments() const {
	return true;
}
