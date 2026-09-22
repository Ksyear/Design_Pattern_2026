#include "controller/PurePursuitController.h"

#include <algorithm>
#include <cmath>

namespace {

constexpr double kPi = 3.14159265358979323846;

double normalizeAngle(double rad)
{
	while (rad > kPi) {
		rad -= 2.0 * kPi;
	}
	while (rad < -kPi) {
		rad += 2.0 * kPi;
	}
	return rad;
}

}

PurePursuitController::PurePursuitController(double desiredLinearVel)
	: desiredLinearVel_(desiredLinearVel)
{
}

Twist PurePursuitController::computeVelocity(const Pose2D& pose,
                                             const Pose2D& goal,
                                             const LaserScan& scan,
                                             const Twist&) const
{
	const double headingToGoal = std::atan2(goal.y - pose.y, goal.x - pose.x);
	const double headingError = normalizeAngle(headingToGoal - pose.yaw);

	Twist cmd;
	cmd.angular_z = 1.2 * headingError;
	cmd.linear_x = desiredLinearVel_ * std::max(0.0, 1.0 - std::abs(headingError) / kPi);

	if (scan.front_range_m < 1.0) {
		cmd.linear_x *= scan.front_range_m;
	}
	return cmd;
}

std::string PurePursuitController::name() const
{
	return "RegulatedPurePursuit";
}
