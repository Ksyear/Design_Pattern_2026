#include "subsystem/MotorDriver.h"

#include <iostream>

void MotorDriver::enable()
{
	std::cout << "    [motor] 드라이버 활성 (전류 루프 ON)\n";
}

void MotorDriver::releaseBrake()
{
	std::cout << "    [motor] 전자 브레이크 해제\n";
}

void MotorDriver::engageBrake()
{
	std::cout << "    [motor] 전자 브레이크 체결\n";
}

void MotorDriver::disable()
{
	std::cout << "    [motor] 드라이버 비활성\n";
}
