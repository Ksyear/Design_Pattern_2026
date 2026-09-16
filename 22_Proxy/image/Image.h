#ifndef IMAGE_IMAGE_H
#define IMAGE_IMAGE_H

// Subject : 진짜 객체와 대리인이 공유하는 인터페이스
//
// 핵심: 진짜 객체와 '같은 인터페이스'를 가진 대리인을 두고, 접근을 통제한다.
//       클라이언트는 프록시인지 진짜인지 구분하지 못한다.
class Image {
public:
	virtual ~Image() = default;
	virtual void display() const = 0;
};

#endif
