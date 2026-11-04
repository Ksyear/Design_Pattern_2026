#include "node/ArmNode.h"

#include <iostream>

#include "estop/EmergencyStopBus.h"

void ArmNode::sendTrajectory(const char* poseName) const
{
	const EmergencyStopBus& estop = EmergencyStopBus::instance();
	if (estop.isLatched()) {
		std::cout << "    [arm] 궤적 전송 거부 (" << estop.reason() << ")\n";
		return;
	}
	std::cout << "    [arm] 목표 자세 " << poseName << " 로 궤적 전송\n";
}
