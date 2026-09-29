#include <iostream>

#include "observer/DockingManager.h"
#include "observer/FleetDashboard.h"
#include "observer/StatusLogger.h"
#include "subject/BatteryPublisher.h"

int main()
{
	BatteryPublisher batteryNode;

	DockingManager docking;
	StatusLogger logger;
	FleetDashboard dashboard;

	std::cout << "===== 1. 구독 등록 =====\n";
	batteryNode.subscribe(&docking);
	batteryNode.subscribe(&logger);
	batteryNode.subscribe(&dashboard);

	std::cout << "\n===== 2. 배터리 값이 올라올 때마다 구독자 전부에게 전달 =====\n";
	std::cout << "  publish 80%\n";
	batteryNode.publish(BatteryState{0.80, 24.6, -2.1});

	std::cout << "  publish 45%\n";
	batteryNode.publish(BatteryState{0.45, 23.4, -3.0});

	std::cout << "  publish 18%  <- 도킹 매니저만 반응한다\n";
	batteryNode.publish(BatteryState{0.18, 22.1, -3.4});

	std::cout << "\n===== 3. 구독 해지 - 관제 화면을 껐다 =====\n";
	batteryNode.unsubscribe(&dashboard);
	std::cout << "  publish 15%\n";
	batteryNode.publish(BatteryState{0.15, 21.8, -3.5});

	std::cout << "\n===== 4. 충전 시작 =====\n";
	std::cout << "  publish 95%\n";
	batteryNode.publish(BatteryState{0.95, 25.2, +1.8});

	return 0;
}
