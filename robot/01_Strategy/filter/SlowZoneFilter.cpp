#include "filter/SlowZoneFilter.h"

#include <algorithm>

SlowZoneFilter::SlowZoneFilter(double maxLinearVel)
	: maxLinearVel_(maxLinearVel)
{
}

Twist SlowZoneFilter::apply(const Twist& raw) const
{
	Twist limited = raw;
	limited.linear_x = std::min(limited.linear_x, maxLinearVel_);
	return limited;
}

std::string SlowZoneFilter::name() const
{
	return "slow-zone";
}
