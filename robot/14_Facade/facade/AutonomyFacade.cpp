#include "facade/AutonomyFacade.h"

#include <iostream>

bool AutonomyFacade::startAutonomy(const char* mapName, double initX, double initY)
{
	std::cout << "  AutonomyFacade::startAutonomy()\n";

	power_.enable24V();
	motors_.enable();
	motors_.releaseBrake();

	lidar_.spinUp();

	localization_.loadMap(mapName);
	localization_.setInitialPose(initX, initY);
	if (!localization_.waitForConvergence()) {
		std::cout << "    측위 실패 - 시동 중단\n";
		shutdown();
		return false;
	}

	nav_.configure();
	nav_.activate();
	navActive_ = true;
	std::cout << "  준비 완료\n";
	return true;
}

void AutonomyFacade::shutdown()
{
	std::cout << "  AutonomyFacade::shutdown()  (역순)\n";
	// 켠 것만 끈다. Unconfigured 노드에 deactivate 는 잘못된 전이다 (21_State 의 전이표).
	// cleanup 까지 해서 Unconfigured 로 돌려 놔야 다음 startAutonomy 의 configure 가 유효하다.
	if (navActive_) {
		nav_.deactivate();
		nav_.cleanup();
		navActive_ = false;
	}
	lidar_.spinDown();
	motors_.engageBrake();  // 반드시 브레이크가 먼저다
	motors_.disable();
	power_.disable24V();
	std::cout << "  정지 완료\n";
}

MotorDriver& AutonomyFacade::motors()
{
	return motors_;
}
