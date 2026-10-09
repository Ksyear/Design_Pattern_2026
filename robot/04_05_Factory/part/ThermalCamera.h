#ifndef PART_THERMALCAMERA_H
#define PART_THERMALCAMERA_H

#include "part/Camera.h"

class ThermalCamera : public Camera {
public:
	std::string spec() const override;
	std::string topic() const override;
};

#endif
