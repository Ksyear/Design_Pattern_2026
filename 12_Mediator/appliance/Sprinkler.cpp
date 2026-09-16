#include "appliance/Sprinkler.h"

#include <iostream>

Sprinkler::Sprinkler() : Appliance("스프링클러") {}

void Sprinkler::doAction(const std::string& action) {
	if (action == "off") std::cout << "  스프링클러: 샤워 15분 전이라 물을 끕니다\n";
	if (action == "on") std::cout << "  스프링클러: 잔디에 물을 줍니다\n";
}
