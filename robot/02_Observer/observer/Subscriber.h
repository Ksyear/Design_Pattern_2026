#ifndef OBSERVER_SUBSCRIBER_H
#define OBSERVER_SUBSCRIBER_H

#include <string>

#include "msg/BatteryState.h"

class Subscriber {
public:
	virtual ~Subscriber() = default;

	virtual void onMessage(const BatteryState& msg) = 0;

	virtual std::string name() const = 0;
};

#endif
