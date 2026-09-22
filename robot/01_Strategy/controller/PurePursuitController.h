#ifndef CONTROLLER_PUREPURSUITCONTROLLER_H
#define CONTROLLER_PUREPURSUITCONTROLLER_H

#include "controller/ControllerPlugin.h"

// 구상 전략 1 - nav2_regulated_pure_pursuit_controller::RegulatedPurePursuitController
//
// 목표를 향한 방향 오차에 비례해 회전하고, 오차가 크면 선속도를 줄인다.
// (실제 RPP 는 lookahead 점의 곡률로 계산하고 곡률/장애물/경사에 따라 속도를 '규제'한다.
//  여기서는 비례 제어로 줄였다 - 이 예제의 목표는 제어 성능이 아니라 구조다.)
class PurePursuitController : public ControllerPlugin {
public:
	explicit PurePursuitController(double desiredLinearVel = 0.45);

	Twist computeVelocity(const Pose2D& pose,
	                      const Pose2D& goal,
	                      const LaserScan& scan) const override;

	std::string name() const override;

private:
	double desiredLinearVel_;  // 전략이 자기 파라미터를 들고 있는 예 (ROS 파라미터에 해당)
};

#endif
