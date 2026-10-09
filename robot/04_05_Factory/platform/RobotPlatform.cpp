#include "platform/RobotPlatform.h"

#include <iostream>
#include <utility>

RobotPlatform::RobotPlatform(std::string name)
	: name_(std::move(name))
{
}

void RobotPlatform::configure()
{
	driveBase_->onConfigure();
}

void RobotPlatform::printBom() const
{
	std::cout << "    센서   : " << lidar_->spec() << "\n";
	std::cout << "             퍼블리시 " << lidar_->topic() << "\n";
	std::cout << "    측위   : " << localizer_->spec() << "\n";
	std::cout << "             기준 좌표계 " << localizer_->frame() << "\n";
	std::cout << "    구동계 : " << driveBase_->spec() << "\n";
}

void RobotPlatform::planPath() const
{
	if (driveBase_->canRotateInPlace()) {
		std::cout << "    경로계획 : 제자리 회전을 써서 좁은 통로도 통과 (NavFn + DWB)\n";
	} else {
		std::cout << "    경로계획 : 최소 회전 반경을 지키는 곡선 경로 (Smac Hybrid-A*)\n";
	}
}

const std::string& RobotPlatform::name() const
{
	return name_;
}
