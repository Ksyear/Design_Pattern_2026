#ifndef OBSERVER_DISPLAY_ELEMENT_H
#define OBSERVER_DISPLAY_ELEMENT_H

// 화면에 뿌리는 책임만 담은 별도 인터페이스.
// Observer 와 나눠 둔 덕분에 "갱신받는 일"과 "보여 주는 일"이 섞이지 않는다.
class DisplayElement {
public:
	virtual ~DisplayElement() = default;
	virtual void display() const = 0;
};

#endif
