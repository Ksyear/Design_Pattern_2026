#ifndef OBSERVER_DOCKINGMANAGER_H
#define OBSERVER_DOCKINGMANAGER_H

#include "observer/Subscriber.h"

class DockingManager : public Subscriber {
public:
	explicit DockingManager(double threshold = 0.20);

	void onMessage(const BatteryState& msg) override;
	std::string name() const override;

private:
	double threshold_;
	bool dockRequested_ = false;
};

#endif
