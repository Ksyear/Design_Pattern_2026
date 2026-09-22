#include "controller/DwbController.h"

#include <algorithm>
#include <array>
#include <cmath>

namespace {

constexpr double kPi = 3.14159265358979323846;
constexpr double kDt = 0.5;
constexpr double kMaxLinearVel = 0.55;
constexpr double kMaxAngularVel = 0.8;
constexpr double kMaxLinearAccel = 0.6;
constexpr double kMaxAngularAccel = 1.6;

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

std::array<double, 3> sampleWindow(double lo, double hi)
{
	return {lo, 0.5 * (lo + hi), hi};
}

}

Twist DwbController::computeVelocity(const Pose2D& pose,
                                     const Pose2D& goal,
                                     const LaserScan& scan,
                                     const Twist& current) const
{
	const double vLo = std::max(0.0, current.linear_x - kMaxLinearAccel * kDt);
	const double vHi = std::min(kMaxLinearVel, current.linear_x + kMaxLinearAccel * kDt);
	const double wLo = std::max(-kMaxAngularVel, current.angular_z - kMaxAngularAccel * kDt);
	const double wHi = std::min(kMaxAngularVel, current.angular_z + kMaxAngularAccel * kDt);

	const double headingToGoal = std::atan2(goal.y - pose.y, goal.x - pose.x);

	Twist best{};
	double bestScore = -1e9;
	for (const double v : sampleWindow(vLo, vHi)) {
		const double stoppingDist = (v * v) / (2.0 * kMaxLinearAccel);
		if (stoppingDist + v * kDt >= scan.front_range_m) {
			continue;
		}

		for (const double w : sampleWindow(wLo, wHi)) {
			const double predictedYaw = pose.yaw + w * kDt;
			const double alignment = -std::abs(normalizeAngle(headingToGoal - predictedYaw));

			const double score = 2.0 * alignment + 0.3 * v;
			if (score > bestScore) {
				bestScore = score;
				best = Twist{v, w};
			}
		}
	}
	return best;
}

std::string DwbController::name() const
{
	return "DWBLocalPlanner";
}
