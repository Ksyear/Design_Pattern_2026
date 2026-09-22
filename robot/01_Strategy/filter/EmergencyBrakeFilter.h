#ifndef FILTER_EMERGENCYBRAKEFILTER_H
#define FILTER_EMERGENCYBRAKEFILTER_H

#include "filter/SpeedFilter.h"

class EmergencyBrakeFilter : public SpeedFilter {
public:
	Twist apply(const Twist& raw) const override;
	std::string name() const override;
};

#endif
