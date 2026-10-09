#include "platform/PatrolRobot.h"

#include <iostream>

void PatrolRobot::assemble(const PartsFactory& parts)
{
	lidar_ = parts.createLidar();
	localizer_ = parts.createLocalizer();
	driveBase_ = parts.createDriveBase();
	camera_ = parts.createCamera();
}

void PatrolRobot::printBom() const
{
	RobotPlatform::printBom();
	std::cout << "    카메라 : " << camera_->spec() << "\n";
	std::cout << "             퍼블리시 " << camera_->topic() << "\n";
}
