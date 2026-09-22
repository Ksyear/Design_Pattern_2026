#include "filter/SlowZoneFilter.h"

#include <algorithm>
#include <cmath>

SlowZoneFilter::SlowZoneFilter(double maxLinearVel)
	: maxLinearVel_(std::max(0.0, maxLinearVel))
{
}

Twist SlowZoneFilter::apply(const Twist& raw) const
{
	const double speed = std::abs(raw.linear_x);
	if (speed <= maxLinearVel_) {
		return raw;
	}

	const double ratio = maxLinearVel_ / speed;
	return Twist{raw.linear_x * ratio, raw.angular_z * ratio};
}

std::string SlowZoneFilter::name() const
{
	return "slow-zone";
}
