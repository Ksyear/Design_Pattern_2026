#include "part/Lidar2D.h"

std::string Lidar2D::spec() const
{
	return "2D 라이다 (RPLIDAR A2, 평면 360도, 12m)";
}

std::string Lidar2D::topic() const
{
	return "/scan (sensor_msgs/LaserScan)";
}
