#ifndef PART_RGBDCAMERA_H
#define PART_RGBDCAMERA_H

#include "part/Camera.h"

class RgbdCamera : public Camera {
public:
	std::string spec() const override;
	std::string topic() const override;
};

#endif
