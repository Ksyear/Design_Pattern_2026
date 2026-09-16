#include "display/StatisticsDisplay.h"

#include <iomanip>
#include <iostream>

void StatisticsDisplay::update(float temp, float /*humidity*/, float /*pressure*/) {
	tempSum_ += temp;
	++count_;
	if (temp > maxTemp_) maxTemp_ = temp;
	if (temp < minTemp_) minTemp_ = temp;
	display();
}

void StatisticsDisplay::display() const {
	std::cout << "평균/최고/최저 온도: " << std::fixed << std::setprecision(1)
	          << (tempSum_ / static_cast<float>(count_)) << "/" << maxTemp_ << "/" << minTemp_
	          << std::defaultfloat << '\n';
}
