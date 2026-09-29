#include "observer/DockingManager.h"

#include <iostream>

DockingManager::DockingManager(double threshold)
	: threshold_(threshold)
{
}

void DockingManager::onMessage(const BatteryState& msg)
{
	if (msg.percentage <= threshold_ && !dockRequested_) {
		dockRequested_ = true;
		std::cout << "    [docking_manager] 배터리 " << static_cast<int>(msg.percentage * 100)
		          << "% - 내비게이션 중단하고 충전 스테이션으로 복귀 요청\n";
	} else if (msg.percentage > threshold_ && dockRequested_) {
		dockRequested_ = false;
		std::cout << "    [docking_manager] 충전 완료 - 임무 재개 가능\n";
	}
}

std::string DockingManager::name() const
{
	return "docking_manager";
}
