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
	const Pose2D pose{0.0, 0.0, 0.0};
	const Pose2D goal{5.0, 2.0, 0.0};
	LaserScan scan{10.0};
	Twist odom{};

	ControllerServer server("deliverybot",
	                        std::make_unique<PurePursuitController>(),
	                        std::make_unique<NoSpeedLimit>());

	std::cout << "===== 1. 기본 조립으로 한 주기 =====\n";
	odom = server.controlLoop(pose, goal, scan, odom);

	std::cout << "\n===== 2. 사람이 많은 구역 진입 - 속도 정책만 교체 =====\n";
	server.setSpeedFilter(std::make_unique<SlowZoneFilter>(0.2));
	odom = server.controlLoop(pose, goal, scan, odom);

	std::cout << "\n===== 3. 정면 0.25m 장애물 - 컨트롤러를 교체 =====\n";
	scan.front_range_m = 0.25;
	server.setPlugin(std::make_unique<StopController>());
	odom = server.controlLoop(pose, goal, scan, odom);

	std::cout << "\n===== 4. 장애물 회피 후 DWB 로 교체 =====\n";
	scan.front_range_m = 3.0;
	server.setPlugin(std::make_unique<DwbController>());
	server.setSpeedFilter(std::make_unique<NoSpeedLimit>());
	odom = server.controlLoop(pose, goal, scan, odom);

	std::cout << "\n===== 5. 비상 정지 - 컨트롤러는 그대로 두고 출력만 막는다 =====\n";
	server.setSpeedFilter(std::make_unique<EmergencyBrakeFilter>());
	odom = server.controlLoop(pose, goal, scan, odom);

	std::cout << "\n===== 6. 같은 상황을 컨트롤러 3종에게 물어보기 =====\n";
	std::vector<std::unique_ptr<ControllerPlugin>> plugins;
	plugins.push_back(std::make_unique<PurePursuitController>());
	plugins.push_back(std::make_unique<DwbController>());
	plugins.push_back(std::make_unique<StopController>());

	const Twist benchOdom{0.30, 0.0};
	for (std::unique_ptr<ControllerPlugin>& plugin : plugins) {
		ControllerServer bench("bench", std::move(plugin), std::make_unique<NoSpeedLimit>());
		bench.controlLoop(pose, goal, scan, benchOdom);
	}

	return 0;
}
