#include "device/Projector.h"

#include <iostream>

void Projector::on() {
	std::cout << "  프로젝터 ON\n";
}

void Projector::off() {
	std::cout << "  프로젝터 OFF\n";
}

void Projector::wideScreenMode() {
	std::cout << "  프로젝터: 와이드 스크린 모드 (16:9)\n";
}
