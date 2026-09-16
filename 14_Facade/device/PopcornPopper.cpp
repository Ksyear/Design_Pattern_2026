#include "device/PopcornPopper.h"

#include <iostream>

void PopcornPopper::on() {
	std::cout << "  팝콘 기계 ON\n";
}

void PopcornPopper::off() {
	std::cout << "  팝콘 기계 OFF\n";
}

void PopcornPopper::pop() {
	std::cout << "  팝콘 튀기는 중\n";
}
