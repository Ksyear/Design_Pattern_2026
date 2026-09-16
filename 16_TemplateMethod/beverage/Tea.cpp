#include "beverage/Tea.h"

#include <iostream>

void Tea::brew() const {
	std::cout << "  찻잎을 우려내는 중\n";
}

void Tea::addCondiments() const {
	std::cout << "  레몬을 추가하는 중\n";
}
