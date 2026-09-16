#include "appliance/CoffeePot.h"

#include <iostream>

CoffeePot::CoffeePot() : Appliance("커피 메이커") {}

void CoffeePot::doAction(const std::string& action) {
	if (action == "brew") std::cout << "  커피 메이커: 커피를 내립니다\n";
	if (action == "skip") std::cout << "  커피 메이커: 주말이라 쉽니다\n";
}
