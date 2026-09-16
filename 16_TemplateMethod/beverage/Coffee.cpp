#include "beverage/Coffee.h"

#include <iostream>

void Coffee::brew() const {
	std::cout << "  필터로 커피를 우려내는 중\n";
}

void Coffee::addCondiments() const {
	std::cout << "  설탕과 우유를 추가하는 중\n";
}
