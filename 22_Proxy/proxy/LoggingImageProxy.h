#ifndef PROXY_LOGGING_IMAGE_PROXY_H
#define PROXY_LOGGING_IMAGE_PROXY_H

#include <memory>

#include "image/Image.h"

// 로깅 프록시 : 호출을 기록한다.
// Image 를 받아 Image 를 구현하므로 프록시끼리 겹쳐 쓸 수 있다.
class LoggingImageProxy : public Image {
public:
	explicit LoggingImageProxy(std::unique_ptr<Image> inner);
	void display() const override;

private:
	std::unique_ptr<Image> inner_;
	mutable int calls_ = 0;
};

#endif
