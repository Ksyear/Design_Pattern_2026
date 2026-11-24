#include "subsystem/NavStack.h"

#include <iostream>

void NavStack::configure()
{
	std::cout << "    [nav2] planner / controller / bt_navigator configure\n";
}

void NavStack::activate()
{
	std::cout << "    [nav2] 라이프사이클 activate - 목표 수신 준비 완료\n";
}

void NavStack::deactivate()
{
	std::cout << "    [nav2] 라이프사이클 deactivate\n";
}

void NavStack::cleanup()
{
	std::cout << "    [nav2] 라이프사이클 cleanup\n";
}
