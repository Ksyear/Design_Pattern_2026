#include "controller/PurePursuitController.h"

#include <algorithm>
#include <cmath>

namespace {

constexpr double kPi = 3.14159265358979323846;

// 각도를 [-pi, pi] 로 접는다. 로봇 코드에서 빠지지 않는 보정이다.
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

}  // namespace

PurePursuitController::PurePursuitController(double desiredLinearVel)
	: desiredLinearVel_(desiredLinearVel)
{
}

Twist PurePursuitController::computeVelocity(const Pose2D& pose,
                                             const Pose2D& goal,
                                             const LaserScan& scan) const
{
	const double headingToGoal = std::atan2(goal.y - pose.y, goal.x - pose.x);
	const double headingError = normalizeAngle(headingToGoal - pose.yaw);

	Twist cmd;
	cmd.angular_z = 1.2 * headingError;
	// 많이 틀어져 있으면 제자리에 가깝게 돌고, 정렬될수록 속도를 낸다 ("규제" 항)
	cmd.linear_x = desiredLinearVel_ * std::max(0.0, 1.0 - std::abs(headingError) / kPi);

	// 앞이 좁으면 스스로도 줄인다 - 전략이 센서를 직접 보는 경우
	if (scan.front_range_m < 1.0) {
		cmd.linear_x *= scan.front_range_m;
	}
	return cmd;
}

std::string PurePursuitController::name() const
{
	return "RegulatedPurePursuit";
}
