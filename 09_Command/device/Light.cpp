#include "device/Light.h"

#include <iostream>
#include <utility>

Light::Light(std::string location) : location_(std::move(location)) {}

void Light::on() {
	std::cout << location_ << " 조명이 켜졌습니다\n";
}

void Light::off() {
	std::cout << location_ << " 조명이 꺼졌습니다\n";
}
