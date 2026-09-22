#ifndef CONTROLLER_STOPCONTROLLER_H
#define CONTROLLER_STOPCONTROLLER_H

#include "controller/ControllerPlugin.h"

// 구상 전략 3 - 무조건 멈춘다.
//
// "아무것도 안 하는 전략" 은 패턴에서 자주 쓰인다. 책의 FlyNoWay 와 같은 자리다.
// 덕분에 ControllerServer 쪽에 "컨트롤러가 없을 때" 분기를 만들 필요가 없다.
// (널 객체 패턴 Null Object 이라고 따로 부르기도 한다)
class StopController : public ControllerPlugin {
public:
	Twist computeVelocity(const Pose2D& pose,
	                      const Pose2D& goal,
	                      const LaserScan& scan) const override;

	std::string name() const override;
};

#endif
