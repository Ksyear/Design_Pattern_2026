#ifndef CONTROLLER_PUREPURSUITCONTROLLER_H
#define CONTROLLER_PUREPURSUITCONTROLLER_H

#include "controller/ControllerPlugin.h"

class PurePursuitController : public ControllerPlugin {
public:
	explicit PurePursuitController(double desiredLinearVel = 0.45);

	Twist computeVelocity(const Pose2D& pose,
	                      const Pose2D& goal,
	                      const LaserScan& scan,
	                      const Twist& current) const override;

	std::string name() const override;

private:
	double desiredLinearVel_;
};

#endif
