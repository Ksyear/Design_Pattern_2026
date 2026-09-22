#ifndef FILTER_SLOWZONEFILTER_H
#define FILTER_SLOWZONEFILTER_H

#include "filter/SpeedFilter.h"

class SlowZoneFilter : public SpeedFilter {
public:
	explicit SlowZoneFilter(double maxLinearVel = 0.2);

	Twist apply(const Twist& raw) const override;
	std::string name() const override;

private:
	double maxLinearVel_;
};

#endif
