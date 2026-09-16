#ifndef DISPLAY_CURRENT_CONDITIONS_DISPLAY_H
#define DISPLAY_CURRENT_CONDITIONS_DISPLAY_H

#include "observer/DisplayElement.h"
#include "observer/Observer.h"

// 구상 옵저버 : 인터페이스 둘을 함께 구현한다 (자바의 implements 두 개와 같다)
class CurrentConditionsDisplay : public Observer, public DisplayElement {
public:
	void update(float temp, float humidity, float pressure) override;
	void display() const override;

private:
	float temperature_ = 0.f;
	float humidity_ = 0.f;
};

#endif
