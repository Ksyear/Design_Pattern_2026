#include "part/RgbdCamera.h"

std::string RgbdCamera::spec() const
{
	return "RGB-D 카메라 (RealSense D435, 0.3~3m 근거리 깊이)";
}

std::string RgbdCamera::topic() const
{
	return "/camera/color/image_raw (sensor_msgs/Image)";
}
