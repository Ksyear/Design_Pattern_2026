#include "part/Lidar3D.h"

std::string Lidar3D::spec() const
{
	return "3D 라이다 (Velodyne VLP-16, 16채널, 100m)";
}

std::string Lidar3D::topic() const
{
	return "/points (sensor_msgs/PointCloud2)";
}
