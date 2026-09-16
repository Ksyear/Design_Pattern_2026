#include "display/ForecastDisplay.h"

#include <iostream>

void ForecastDisplay::update(float /*temp*/, float /*humidity*/, float pressure) {
	lastPressure_ = currentPressure_;
	currentPressure_ = pressure;
	display();
}

void ForecastDisplay::display() const {
	std::cout << "기상 예보: ";
	if (currentPressure_ > lastPressure_)      std::cout << "날씨가 좋아지고 있습니다!\n";
	else if (currentPressure_ == lastPressure_) std::cout << "지금과 비슷할 것 같습니다\n";
	else                                        std::cout << "쌀쌀하고 비가 올 것 같습니다\n";
}
