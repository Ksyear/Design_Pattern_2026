#include "subject/WeatherData.h"

#include <algorithm>

void WeatherData::registerObserver(const std::shared_ptr<Observer>& o) {
	observers_.emplace_back(o);
}

void WeatherData::removeObserver(const std::shared_ptr<Observer>& o) {
	observers_.erase(
		std::remove_if(observers_.begin(), observers_.end(),
			[&](const std::weak_ptr<Observer>& w) {
				auto sp = w.lock();
				return !sp || sp == o;
			}),
		observers_.end());
}

void WeatherData::notifyObservers() {
	// 순회 중에 죽은 옵저버를 함께 정리한다
	for (auto it = observers_.begin(); it != observers_.end();) {
		if (auto sp = it->lock()) {
			sp->update(temperature_, humidity_, pressure_);
			++it;
		} else {
			it = observers_.erase(it);
		}
	}
}

void WeatherData::setMeasurements(float temperature, float humidity, float pressure) {
	temperature_ = temperature;
	humidity_ = humidity;
	pressure_ = pressure;
	measurementsChanged();
}

void WeatherData::measurementsChanged() {
	notifyObservers();
}
