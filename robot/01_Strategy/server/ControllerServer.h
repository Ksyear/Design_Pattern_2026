#ifndef SERVER_CONTROLLERSERVER_H
#define SERVER_CONTROLLERSERVER_H

#include <memory>
#include <string>

#include "controller/ControllerPlugin.h"
#include "filter/SpeedFilter.h"
#include "msg/Types.h"

// Context - ROS 2 Nav2 의 controller_server 노드 자리.
//
// 이 헤더와 구현 어디에도 PurePursuitController / DwbController 라는 이름이 없다.
// 아는 것은 ControllerPlugin, SpeedFilter 두 인터페이스뿐이다.
// 무엇이 꽂혀 있는지는 조립하는 쪽(main)만 안다
// -> 실제 Nav2 에서 그 "조립하는 쪽" 이 pluginlib 과 파라미터 파일이다.
//
// 불변식 : 전략 둘은 항상 존재한다.
//   생성자에서 받고 세터도 nullptr 을 거부하므로 controlLoop 안에
//   if (plugin_) 같은 방어 코드가 필요 없다.
class ControllerServer {
public:
	ControllerServer(std::string robotName,
	                 std::unique_ptr<ControllerPlugin> plugin,
	                 std::unique_ptr<SpeedFilter> filter);

	// 제어 주기 한 번. 계산은 전부 전략에 넘기고 이 함수는 위임과 퍼블리시만 한다.
	// 여기에 알고리즘이 한 줄도 없다는 것이 이 패턴의 결과다.
	void controlLoop(const Pose2D& pose, const Pose2D& goal, const LaserScan& scan) const;

	// 실행 중 교체 - Nav2 로 치면 FollowPath.plugin 을 바꿔 끼우는 것.
	// 상속으로 행동을 물려받았다면 불가능한 지점이다.
	void setPlugin(std::unique_ptr<ControllerPlugin> plugin);
	void setSpeedFilter(std::unique_ptr<SpeedFilter> filter);

	const std::string& robotName() const;

private:
	void publishCmdVel(const Twist& cmd) const;  // /cmd_vel 퍼블리시 흉내

	// protected 가 아니라 private : 파생 클래스도 직접 건드릴 수 없다
	std::unique_ptr<ControllerPlugin> plugin_;
	std::unique_ptr<SpeedFilter> filter_;
	std::string robotName_;
};

#endif
