#include "tv/LG.h"

#include <iostream>

void LG::on() {
	std::cout << "  [LG] 전원 ON\n";
}

void LG::off() {
	std::cout << "  [LG] 전원 OFF\n";
}

void LG::tuneChannel(int channel) {
	// 제조사마다 내부 호출 방식이 다르다 - 이 차이를 추상화 쪽이 몰라도 된다
	std::cout << "  [LG] switchToChannel(" << channel << ") 호출\n";
}

std::string LG::brand() const {
	return "LG";
}
