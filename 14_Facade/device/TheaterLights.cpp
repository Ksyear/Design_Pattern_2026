#include "device/TheaterLights.h"

#include <iostream>

void TheaterLights::on() {
	std::cout << "  조명 ON\n";
}

void TheaterLights::dim(int level) {
	std::cout << "  조명을 " << level << "%로 낮춤\n";
}
