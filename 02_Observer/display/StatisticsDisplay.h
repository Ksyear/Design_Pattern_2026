#ifndef DISPLAY_STATISTICS_DISPLAY_H
#define DISPLAY_STATISTICS_DISPLAY_H

#include "observer/DisplayElement.h"
#include "observer/Observer.h"

// 구상 옵저버 : 같은 통보를 받아도 옵저버마다 쓰는 값이 다르다
class StatisticsDisplay : public Observer, public DisplayElement {
public:
	void update(float temp, float humidity, float pressure) override;
	void display() const override;

private:
	float tempSum_ = 0.f;
	int count_ = 0;
	float maxTemp_ = -1000.f;
	float minTemp_ = 1000.f;
};

#endif
