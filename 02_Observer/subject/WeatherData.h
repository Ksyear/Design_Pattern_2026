#ifndef SUBJECT_WEATHER_DATA_H
#define SUBJECT_WEATHER_DATA_H

#include <memory>
#include <vector>

#include "subject/Subject.h"

// 구상 주제 : 주제 하나 : 옵저버 여럿 의 일대다 의존성을 들고 있다.
//
// C++ 주의: 옵저버가 주제보다 먼저 소멸하면 dangling 포인터가 된다.
//           여기서는 weak_ptr 로 그 문제를 구조적으로 막았다.
class WeatherData : public Subject {
public:
	void registerObserver(const std::shared_ptr<Observer>& o) override;
	void removeObserver(const std::shared_ptr<Observer>& o) override;
	void notifyObservers() override;

	// 기상 관측값이 갱신되면 스스로 notify를 부른다
	void setMeasurements(float temperature, float humidity, float pressure);

private:
	void measurementsChanged();

	std::vector<std::weak_ptr<Observer>> observers_;
	float temperature_ = 0.f;
	float humidity_ = 0.f;
	float pressure_ = 0.f;
};

#endif
