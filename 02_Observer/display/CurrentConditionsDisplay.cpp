#include "display/CurrentConditionsDisplay.h"

#include <iostream>

void CurrentConditionsDisplay::update(float temp, float humidity, float /*pressure*/) {
	temperature_ = temp;
	humidity_ = humidity;
	display();
}

void CurrentConditionsDisplay::display() const {
	std::cout << "현재 상태: 온도 " << temperature_ << "F, 습도 " << humidity_ << "%\n";
}
