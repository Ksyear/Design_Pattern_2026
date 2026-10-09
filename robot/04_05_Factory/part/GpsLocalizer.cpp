#include "part/GpsLocalizer.h"

std::string GpsLocalizer::spec() const
{
	return "RTK-GPS + IMU 융합 (robot_localization 의 navsat_transform)";
}

std::string GpsLocalizer::frame() const
{
	return "utm";
}
