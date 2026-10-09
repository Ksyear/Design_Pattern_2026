#include "bringup/WarehouseBringup.h"

#include "factory/IndoorPartsFactory.h"
#include "platform/DeliveryRobot.h"
#include "platform/PatrolRobot.h"

WarehouseBringup::WarehouseBringup()
	: RobotBringup("warehouse", std::make_unique<IndoorPartsFactory>())
{
}

std::unique_ptr<RobotPlatform> WarehouseBringup::createRobot(const std::string& mission) const
{
	if (mission == "delivery") {
		return std::make_unique<DeliveryRobot>("창고 배송 로봇");
	}
	if (mission == "patrol") {
		return std::make_unique<PatrolRobot>("창고 순찰 로봇");
	}
	return nullptr;
}
