#include "mission/Mission.h"

#include <iomanip>
#include <iostream>
#include <utility>

Mission::Mission(std::string robotId,
                 std::vector<Waypoint> waypoints,
                 double speedLimit,
                 std::vector<std::string> recoveries,
                 bool looping)
	: robotId_(std::move(robotId)),
	  waypoints_(std::move(waypoints)),
	  speedLimit_(speedLimit),
	  recoveries_(std::move(recoveries)),
	  looping_(looping)
{
}

void Mission::print() const
{
	std::cout << "  [" << robotId_ << "] 임무 " << (looping_ ? "(무한 반복)" : "(1회)") << '\n';
	std::cout << "    속도 상한 " << std::fixed << std::setprecision(2) << speedLimit_ << " m/s\n";
	std::cout << "    경유지 " << waypoints_.size() << "개\n";
	for (const Waypoint& wp : waypoints_) {
		std::cout << "      - " << wp.label << " (" << wp.x << ", " << wp.y << ")\n";
	}
	std::cout << "    실패 시 복구 동작 : ";
	if (recoveries_.empty()) {
		std::cout << "없음 (실패하면 그대로 중단)";
	} else {
		for (std::size_t i = 0; i < recoveries_.size(); ++i) {
			std::cout << recoveries_[i] << (i + 1 < recoveries_.size() ? " -> " : "");
		}
	}
	std::cout << "\n";
}

const std::vector<Waypoint>& Mission::waypoints() const
{
	return waypoints_;
}
