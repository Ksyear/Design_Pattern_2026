#include "observer/StatusLogger.h"

#include <iomanip>
#include <iostream>

void StatusLogger::onMessage(const BatteryState& msg)
{
	++count_;
	std::cout << "    [status_logger] #" << count_ << "  " << std::fixed << std::setprecision(1)
	          << msg.voltage << "V  " << msg.current << "A  "
	          << (msg.percentage * 100.0) << "%\n";
}

std::string StatusLogger::name() const
{
	return "status_logger";
}
