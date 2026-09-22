#ifndef CONTROLLER_CONTROLLERPLUGIN_H
#define CONTROLLER_CONTROLLERPLUGIN_H

#include <string>

#include "msg/Types.h"

// Strategy 인터페이스 - 실제 ROS 2 의 nav2_core::Controller 자리다.
//
// 진짜 Nav2 인터페이스에는 configure() / activate() / deactivate() / cleanup() /
// setPlan() / setSpeedLimit() / computeVelocityCommands() 가 들어 있다.
// 여기서는 패턴만 남기려고 "속도를 계산한다" 하나로 줄였다.
//
// 달라지는 부분은 딱 하나다 : 같은 (현재 위치, 목표, 스캔) 을 받고도
// 어떤 속도를 낼지가 구현마다 다르다. 그 한 줄을 인터페이스 뒤로 뽑아낸 것이 이 패턴이다.
class ControllerPlugin {
public:
	virtual ~ControllerPlugin() = default;  // 다형적 기반 클래스에는 반드시 필요

	virtual Twist computeVelocity(const Pose2D& pose,
	                              const Pose2D& goal,
	                              const LaserScan& scan) const = 0;

	virtual std::string name() const = 0;
};

#endif
