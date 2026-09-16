#ifndef DISPLAY_FORECAST_DISPLAY_H
#define DISPLAY_FORECAST_DISPLAY_H

#include "observer/DisplayElement.h"
#include "observer/Observer.h"

// 구상 옵저버 : 기압 변화만 본다
class ForecastDisplay : public Observer, public DisplayElement {
public:
	void update(float temp, float humidity, float pressure) override;
	void display() const override;

private:
	float currentPressure_ = 29.92f;
	float lastPressure_ = 29.92f;
};

#endif
