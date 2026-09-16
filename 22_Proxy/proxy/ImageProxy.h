#ifndef PROXY_IMAGE_PROXY_H
#define PROXY_IMAGE_PROXY_H

#include <memory>
#include <string>

#include "image/Image.h"
#include "image/RealImage.h"

// 가상(virtual) 프록시 : 비싼 객체 생성을 미룬다.
// 같은 인터페이스라서 클라이언트는 교체된 줄 모른다.
class ImageProxy : public Image {
public:
	explicit ImageProxy(std::string filename);

	void display() const override;

private:
	std::string filename_;
	mutable std::unique_ptr<RealImage> real_;   // const 메소드에서 만들어야 하므로 mutable
};

#endif
