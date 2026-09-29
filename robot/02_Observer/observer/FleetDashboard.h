#ifndef OBSERVER_FLEETDASHBOARD_H
#define OBSERVER_FLEETDASHBOARD_H

#include "observer/Subscriber.h"

class FleetDashboard : public Subscriber {
public:
	void onMessage(const BatteryState& msg) override;
	std::string name() const override;
};

#endif
