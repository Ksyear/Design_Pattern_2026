#include "scan/RawLidar.h"

LaserScan RawLidar::read() const
{
	return LaserScan{{1.20, 1.18, 0.00, 1.25, 41.70, 1.30, 1.28, 55.00}};
}

double RawLidar::latencyMs() const
{
	return 2.0;
}

std::string RawLidar::pipeline() const
{
	return "RawLidar";
}
