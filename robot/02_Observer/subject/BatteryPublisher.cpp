#include "subject/BatteryPublisher.h"

#include <algorithm>
#include <iostream>

void BatteryPublisher::subscribe(Subscriber* sub)
{
	if (sub == nullptr) {
		return;
	}
	subscribers_.push_back(sub);
	std::cout << "  [topic] /battery_state <- " << sub->name() << " 구독 시작\n";
}

void BatteryPublisher::unsubscribe(Subscriber* sub)
{
	const auto it = std::find(subscribers_.begin(), subscribers_.end(), sub);
	if (it != subscribers_.end()) {
		std::cout << "  [topic] /battery_state <- " << (*it)->name() << " 구독 해지\n";
		subscribers_.erase(it);
	}
}

void BatteryPublisher::notify()
{
	for (Subscriber* sub : subscribers_) {
		sub->onMessage(state_);
	}
}

void BatteryPublisher::publish(const BatteryState& msg)
{
	state_ = msg;
	notify();
}

const BatteryState& BatteryPublisher::state() const
{
	return state_;
}
