#include "proxy/ImageProxy.h"

#include <iostream>
#include <utility>

ImageProxy::ImageProxy(std::string filename) : filename_(std::move(filename)) {}

void ImageProxy::display() const {
	if (!real_) {
		std::cout << "  (아직 로딩 전 - 플레이스홀더 표시)\n";
		real_ = std::make_unique<RealImage>(filename_);   // 늦은 생성(lazy)
	}
	real_->display();
}
