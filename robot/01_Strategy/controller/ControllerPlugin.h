#ifndef CONTROLLER_CONTROLLERPLUGIN_H
#define CONTROLLER_CONTROLLERPLUGIN_H

#include <string>

#include "msg/Types.h"

class ControllerPlugin {
public:
	virtual ~ControllerPlugin() = default;

	virtual Twist computeVelocity(const Pose2D& pose,
	                              const Pose2D& goal,
	                              const LaserScan& scan,
	                              const Twist& current) const = 0;

	virtual std::string name() const = 0;
};

#endif
