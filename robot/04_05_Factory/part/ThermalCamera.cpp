#include "part/ThermalCamera.h"

std::string ThermalCamera::spec() const
{
	return "열화상 카메라 (FLIR Boson, 조명 없는 야간에도 사람을 본다)";
}

std::string ThermalCamera::topic() const
{
	return "/thermal/image_raw (sensor_msgs/Image)";
}
