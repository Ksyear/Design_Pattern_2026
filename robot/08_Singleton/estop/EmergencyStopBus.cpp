#include "estop/EmergencyStopBus.h"

#include <iostream>

EmergencyStopBus& EmergencyStopBus::instance()
{
	// 처음 호출될 때 한 번만 만들어지고, 프로그램이 끝날 때 파괴된다.
	// 자바의 지연 초기화 싱글턴과 같은 효과를 문법 하나로 얻는다.
	static EmergencyStopBus bus;
	return bus;
}

void EmergencyStopBus::trigger(const std::string& reason)
{
	latched_ = true;
	reason_ = reason;
	++triggerCount_;
	std::cout << "  !! E-STOP 래치 : " << reason_ << '\n';
}

void EmergencyStopBus::reset()
{
	latched_ = false;
	reason_ = "(정상)";
	std::cout << "  -- E-STOP 해제 (사람이 버튼을 복귀시킴)\n";
}

bool EmergencyStopBus::isLatched() const
{
	return latched_;
}

const std::string& EmergencyStopBus::reason() const
{
	return reason_;
}

int EmergencyStopBus::triggerCount() const
{
	return triggerCount_;
}
