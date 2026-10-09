#include "bringup/CampusBringup.h"

#include "factory/OutdoorPartsFactory.h"
#include "platform/DeliveryRobot.h"
#include "platform/PatrolRobot.h"

CampusBringup::CampusBringup()
	: RobotBringup("campus", std::make_unique<OutdoorPartsFactory>())
{
}

std::unique_ptr<RobotPlatform> CampusBringup::createRobot(const std::string& mission) const
{
	if (mission == "delivery") {
		return std::make_unique<DeliveryRobot>("캠퍼스 배송 로봇");
	}
	if (mission == "patrol") {
		return std::make_unique<PatrolRobot>("캠퍼스 순찰 로봇");
	}
	return nullptr;
}
