#ifndef CONTROLLER_STOPCONTROLLER_H
#define CONTROLLER_STOPCONTROLLER_H

#include "controller/ControllerPlugin.h"

class StopController : public ControllerPlugin {
public:
	Twist computeVelocity(const Pose2D& pose,
	                      const Pose2D& goal,
	                      const LaserScan& scan,
	                      const Twist& current) const override;

	std::string name() const override;
};

#endif
