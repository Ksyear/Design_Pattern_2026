#include "subsystem/PowerRail.h"

#include <iostream>

void PowerRail::enable24V()
{
	on_ = true;
	std::cout << "    [power] 24V 레일 ON\n";
}

void PowerRail::disable24V()
{
	on_ = false;
	std::cout << "    [power] 24V 레일 OFF\n";
}

bool PowerRail::isOn() const
{
	return on_;
}
