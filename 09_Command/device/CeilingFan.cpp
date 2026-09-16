#include "device/CeilingFan.h"

#include <iostream>
#include <utility>

CeilingFan::CeilingFan(std::string location) : location_(std::move(location)) {}

void CeilingFan::setSpeed(Speed s) {
	speed_ = s;
	static const char* names[] = {"꺼짐", "약", "중", "강"};
	std::cout << location_ << " 선풍기 속도: " << names[s] << '\n';
}

CeilingFan::Speed CeilingFan::getSpeed() const {
	return speed_;
}
