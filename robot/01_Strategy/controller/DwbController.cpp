#include "controller/DwbController.h"

#include <array>
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

}  // namespace

Twist DwbController::computeVelocity(const Pose2D& pose,
                                     const Pose2D& goal,
                                     const LaserScan& scan) const
{
	// 동적 윈도 : 지금 낼 수 있는 속도 후보들
	const std::array<Twist, 3> window{
		Twist{0.50, -0.4},
		Twist{0.55, 0.0},
		Twist{0.50, 0.4},
	};

	const double headingToGoal = std::atan2(goal.y - pose.y, goal.x - pose.x);

	Twist best{};
	double bestScore = -1e9;
	for (const Twist& candidate : window) {
		// 이 후보로 한 스텝 갔다고 치고 방향이 얼마나 맞는지 점수를 낸다
		const double predictedYaw = pose.yaw + candidate.angular_z * 0.5;
		const double alignment = -std::abs(normalizeAngle(headingToGoal - predictedYaw));
		const double clearance = (scan.front_range_m < 1.0) ? -candidate.linear_x : 0.0;

		const double score = 2.0 * alignment + 1.0 * clearance;
		if (score > bestScore) {
			bestScore = score;
			best = candidate;
		}
	}
	return best;
}

std::string DwbController::name() const
{
	return "DWBLocalPlanner";
}
