#ifndef CONTROLLER_DWBCONTROLLER_H
#define CONTROLLER_DWBCONTROLLER_H

#include "controller/ControllerPlugin.h"

// 구상 전략 2 - dwb_core::DWBLocalPlanner (Dynamic Window Approach)
//
// 후보 속도들을 만들어 놓고 점수를 매겨 제일 좋은 것을 고르는 방식이다.
// 여기서는 후보 3개에 "목표를 향하는가 / 장애물에서 먼가" 두 점수만 매긴다.
// 중요한 것은 계산 방식이 위의 Pure Pursuit 과 완전히 다른데도
// ControllerServer 는 그 차이를 전혀 모른다는 점이다.
class DwbController : public ControllerPlugin {
public:
	Twist computeVelocity(const Pose2D& pose,
	                      const Pose2D& goal,
	                      const LaserScan& scan) const override;

	std::string name() const override;
};

#endif
