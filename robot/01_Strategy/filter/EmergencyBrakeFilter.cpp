#include "filter/EmergencyBrakeFilter.h"

Twist EmergencyBrakeFilter::apply(const Twist&) const
{
	return Twist{0.0, 0.0};
}

std::string EmergencyBrakeFilter::name() const
{
	return "e-stop";
}
