#include "sensor/Lidar2D.h"

LaserScan Lidar2D::scan() const
{
	return LaserScan{"laser_link", {2.31, 2.28, 2.35, 0.00, 1.97, 2.02}};
}

std::string Lidar2D::name() const
{
	return "RPLIDAR A2";
}
