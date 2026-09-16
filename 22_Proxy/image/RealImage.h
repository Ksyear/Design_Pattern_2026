#ifndef IMAGE_REAL_IMAGE_H
#define IMAGE_REAL_IMAGE_H

#include <string>

#include "image/Image.h"

// RealSubject : 만드는 데 비용이 큰 객체
class RealImage : public Image {
public:
	explicit RealImage(std::string filename);
	void display() const override;

private:
	void loadFromDisk() const;
	std::string filename_;
};

#endif
