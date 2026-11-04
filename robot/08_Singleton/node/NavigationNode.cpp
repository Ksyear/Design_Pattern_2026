#include "node/NavigationNode.h"

#include <iostream>

#include "estop/EmergencyStopBus.h"

void NavigationNode::publishCmdVel(double linearX) const
{
	// 생성자로 받지 않고 전역에서 꺼내 쓴다.
	// 편한 만큼 의존성이 숨는다 - 이 노드를 테스트하려면 전역 상태를 손봐야 한다.
	// 그 불편함이 곧 싱글턴의 비용이다.
	const EmergencyStopBus& estop = EmergencyStopBus::instance();
	if (estop.isLatched()) {
		std::cout << "    [nav] 정지 유지 (" << estop.reason() << ")\n";
		return;
	}
	std::cout << "    [nav] /cmd_vel linear.x=" << linearX << '\n';
}
