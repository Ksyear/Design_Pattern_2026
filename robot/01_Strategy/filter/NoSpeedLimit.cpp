#include "filter/NoSpeedLimit.h"

Twist NoSpeedLimit::apply(const Twist& raw) const
{
	return raw;
}

std::string NoSpeedLimit::name() const
{
	return "none";
}
