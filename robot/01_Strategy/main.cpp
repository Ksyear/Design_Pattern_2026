// 전략 패턴 (Strategy) - ROS 2 Nav2 컨트롤러 플러그인
//
// 책의 오리 시뮬레이션(../../01_Strategy)과 같은 패턴을 로봇 도메인으로 옮긴 것이다.
//   Duck            -> ControllerServer   (Context)
//   FlyBehavior     -> ControllerPlugin   ("경로를 어떻게 따라갈 것인가")
//   QuackBehavior   -> SpeedFilter        ("계산한 속도를 그대로 낼 것인가")
//   setFlyBehavior  -> setPlugin          (실행 중 교체)
//
// 실제 ROS 2 대응
//   ControllerPlugin      = nav2_core::Controller
//   computeVelocity()     = computeVelocityCommands()
//   setPlugin()           = pluginlib 로더 + FollowPath.plugin 파라미터
//   publishCmdVel()       = /cmd_vel 토픽 퍼블리시
//   SpeedFilter           = nav2_costmap_2d 의 Speed Filter 플러그인
//
// 폴더 지도
//   msg/         메시지 구조체   - Twist / Pose2D / LaserScan (데이터만)
//   controller/  주행 전략 축    - ControllerPlugin.h + 구상 3개
//   filter/      속도 정책 축    - SpeedFilter.h + 구상 3개
//   server/      Context        - ControllerServer.* (전략을 들고 위임만 한다)
//
// controller/ 와 filter/ 는 서로를 전혀 모르고, server/ 만 둘을 인터페이스로 안다.
#include <iostream>
#include <memory>
#include <vector>

#include "controller/DwbController.h"
#include "controller/PurePursuitController.h"
#include "controller/StopController.h"
#include "filter/EmergencyBrakeFilter.h"
#include "filter/NoSpeedLimit.h"
#include "filter/SlowZoneFilter.h"
#include "msg/Types.h"
#include "server/ControllerServer.h"

int main()
{
	const Pose2D pose{0.0, 0.0, 0.0};   // 로봇은 원점에서 +x 를 보고 있다
	const Pose2D goal{5.0, 2.0, 0.0};   // 목표는 왼쪽 앞
	LaserScan scan{10.0};               // 앞이 비어 있다

	// 조립 : 어떤 구현을 쓸지는 여기서만 결정한다 (Nav2 의 파라미터 파일에 해당)
	ControllerServer server("deliverybot",
	                        std::make_unique<PurePursuitController>(),
	                        std::make_unique<NoSpeedLimit>());

	std::cout << "===== 1. 기본 조립으로 한 주기 =====\n";
	server.controlLoop(pose, goal, scan);

	std::cout << "\n===== 2. 사람이 많은 구역 진입 - 속도 정책만 교체 =====\n";
	// 컨트롤러는 그대로다. 두 축을 나눠 뒀기 때문에 한쪽만 갈아 끼울 수 있다.
	server.setSpeedFilter(std::make_unique<SlowZoneFilter>(0.2));
	server.controlLoop(pose, goal, scan);

	std::cout << "\n===== 3. 정면 0.25m 장애물 - 컨트롤러를 교체 =====\n";
	// 실제 Nav2 에서는 비헤이비어 트리가 이 판단을 내려 컨트롤러/복구 동작을 바꿔 끼운다.
	scan.front_range_m = 0.25;
	server.setPlugin(std::make_unique<StopController>());
	server.controlLoop(pose, goal, scan);

	std::cout << "\n===== 4. 장애물 회피 후 DWB 로 교체 =====\n";
	scan.front_range_m = 3.0;
	server.setPlugin(std::make_unique<DwbController>());
	server.setSpeedFilter(std::make_unique<NoSpeedLimit>());
	server.controlLoop(pose, goal, scan);

	std::cout << "\n===== 5. 비상 정지 - 컨트롤러는 그대로 두고 출력만 막는다 =====\n";
	server.setSpeedFilter(std::make_unique<EmergencyBrakeFilter>());
	server.controlLoop(pose, goal, scan);

	// 원칙 확인 : "구현이 아닌 인터페이스에 맞춰 프로그래밍한다"
	//
	// 아래 루프에는 구상 컨트롤러 이름이 vector 를 채울 때 말고는 나오지 않는다.
	// 아는 것은 ControllerPlugin 하나뿐이라, 컨트롤러가 몇 개로 늘어나든
	// 비교 루프는 한 글자도 바뀌지 않는다.
	//
	// 두 축이 여기서 같이 드러난다.
	//   세로축(상속) : ControllerPlugin* 하나로 여러 구현을 다룬다        -> 다형성
	//   가로축(구성) : 같은 서버가 서로 다른 구현을 들고 있다             -> 전략
	std::cout << "\n===== 6. 같은 상황을 컨트롤러 3종에게 물어보기 =====\n";
	std::vector<std::unique_ptr<ControllerPlugin>> plugins;
	plugins.push_back(std::make_unique<PurePursuitController>());
	plugins.push_back(std::make_unique<DwbController>());
	plugins.push_back(std::make_unique<StopController>());

	// unique_ptr 는 복사가 안 되므로 소유권을 옮겨 준다(std::move).
	// 그래서 참조에 const 를 붙이지 않는다 - 옮기고 나면 plugins 쪽은 비게 된다.
	for (std::unique_ptr<ControllerPlugin>& plugin : plugins) {
		ControllerServer bench("bench", std::move(plugin), std::make_unique<NoSpeedLimit>());
		bench.controlLoop(pose, goal, scan);
	}

	return 0;
}
