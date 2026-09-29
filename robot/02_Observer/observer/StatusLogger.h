#ifndef OBSERVER_STATUSLOGGER_H
#define OBSERVER_STATUSLOGGER_H

#include "observer/Subscriber.h"

class StatusLogger : public Subscriber {
public:
	void onMessage(const BatteryState& msg) override;
	std::string name() const override;

private:
	int count_ = 0;
};

#endif
