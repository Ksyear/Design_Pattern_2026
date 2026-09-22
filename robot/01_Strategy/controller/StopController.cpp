#include "controller/StopController.h"

Twist StopController::computeVelocity(const Pose2D&, const Pose2D&, const LaserScan&, const Twist&) const
{
	return Twist{0.0, 0.0};
}

std::string StopController::name() const
{
	return "StopAndWait";
}
