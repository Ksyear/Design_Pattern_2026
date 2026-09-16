#include "device/StreamingPlayer.h"

#include <iostream>

void StreamingPlayer::on() {
	std::cout << "  스트리밍 플레이어 ON\n";
}

void StreamingPlayer::off() {
	std::cout << "  스트리밍 플레이어 OFF\n";
}

void StreamingPlayer::play(const std::string& movie) {
	std::cout << "  재생 시작: " << movie << '\n';
}

void StreamingPlayer::stop() {
	std::cout << "  재생 정지\n";
}
