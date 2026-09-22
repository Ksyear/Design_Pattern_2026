#include "controller/StopController.h"

// 파라미터 이름을 아예 쓰지 않는다 -> -Wunused-parameter 경고를 피하는 정석
Twist StopController::computeVelocity(const Pose2D&, const Pose2D&, const LaserScan&) const
{
	return Twist{0.0, 0.0};
}

std::string StopController::name() const
{
	return "StopAndWait";
}
