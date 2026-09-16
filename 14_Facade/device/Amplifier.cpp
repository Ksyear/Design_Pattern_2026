#include "device/Amplifier.h"

#include <iostream>

void Amplifier::on() {
	std::cout << "  앰프 ON\n";
}

void Amplifier::off() {
	std::cout << "  앰프 OFF\n";
}

void Amplifier::setStreamingPlayer() {
	std::cout << "  앰프: 스트리밍 플레이어를 입력으로 설정\n";
}

void Amplifier::setSurroundSound() {
	std::cout << "  앰프: 서라운드 사운드 모드\n";
}

void Amplifier::setVolume(int level) {
	std::cout << "  앰프: 볼륨 " << level << '\n';
}
