#include "tv/Sony.h"

#include <iostream>

void Sony::on() {
	std::cout << "  [소니] 전원 ON\n";
}

void Sony::off() {
	std::cout << "  [소니] 전원 OFF\n";
}

void Sony::tuneChannel(int channel) {
	std::cout << "  [소니] setChannel(" << channel << ") 호출\n";
}

std::string Sony::brand() const {
	return "소니";
}
