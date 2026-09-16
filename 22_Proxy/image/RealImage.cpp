#include "image/RealImage.h"

#include <iostream>
#include <utility>

RealImage::RealImage(std::string filename) : filename_(std::move(filename)) {
	loadFromDisk();   // 생성만 해도 비싸다
}

void RealImage::display() const {
	std::cout << "  [표시] " << filename_ << '\n';
}

void RealImage::loadFromDisk() const {
	std::cout << "  [디스크 로딩... 3초 걸림] " << filename_ << '\n';
}
