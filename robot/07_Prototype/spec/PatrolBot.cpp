#include "spec/PatrolBot.h"

PatrolBot::PatrolBot()
	: RobotSpec("SEC-50", {"3d_lidar", "thermal_camera", "mic_array", "imu"}, 1.2)
{
}

std::unique_ptr<RobotSpec> PatrolBot::clone() const
{
	return std::unique_ptr<RobotSpec>(new PatrolBot(*this));
}

std::string PatrolBot::role() const
{
	return "순찰";
}
