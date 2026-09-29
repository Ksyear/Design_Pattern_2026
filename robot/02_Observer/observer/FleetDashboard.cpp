#include "observer/FleetDashboard.h"

#include <iostream>
#include <string>

void FleetDashboard::onMessage(const BatteryState& msg)
{
	const int blocks = static_cast<int>(msg.percentage * 10.0 + 0.5);
	std::cout << "    [fleet_dashboard] [" << std::string(static_cast<std::size_t>(blocks), '#')
	          << std::string(static_cast<std::size_t>(10 - blocks), '.') << "]\n";
}

std::string FleetDashboard::name() const
{
	return "fleet_dashboard";
}
