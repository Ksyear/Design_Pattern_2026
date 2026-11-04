#include "builder/MissionBuilder.h"

#include <stdexcept>
#include <utility>

MissionBuilder::MissionBuilder(std::string robotId)
	: robotId_(std::move(robotId))
{
}

MissionBuilder& MissionBuilder::waypoint(const std::string& label, double x, double y)
{
	waypoints_.push_back(Waypoint{label, x, y});
	return *this;
}

MissionBuilder& MissionBuilder::speedLimit(double metersPerSecond)
{
	speedLimit_ = metersPerSecond;
	return *this;
}

MissionBuilder& MissionBuilder::recovery(const std::string& behavior)
{
	recoveries_.push_back(behavior);
	return *this;
}

MissionBuilder& MissionBuilder::loopForever()
{
	looping_ = true;
	return *this;
}

Mission MissionBuilder::build() const
{
	// 빌더가 검증을 맡는다 -> 잘못된 임무가 아예 만들어지지 않는다
	if (waypoints_.empty()) {
		throw std::invalid_argument("경유지가 하나도 없는 임무는 만들 수 없습니다");
	}
	return Mission(robotId_, waypoints_, speedLimit_, recoveries_, looping_);
}
