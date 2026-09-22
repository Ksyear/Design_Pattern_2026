#ifndef CONTROLLER_DWBCONTROLLER_H
#define CONTROLLER_DWBCONTROLLER_H

#include "controller/ControllerPlugin.h"

class DwbController : public ControllerPlugin {
public:
	Twist computeVelocity(const Pose2D& pose,
	                      const Pose2D& goal,
	                      const LaserScan& scan,
	                      const Twist& current) const override;

	std::string name() const override;
};

#endif
