#ifndef BRINGUP_WAREHOUSEBRINGUP_H
#define BRINGUP_WAREHOUSEBRINGUP_H

#include "bringup/RobotBringup.h"

class WarehouseBringup : public RobotBringup {
public:
	WarehouseBringup();

protected:
	std::unique_ptr<RobotPlatform> createRobot(const std::string& mission) const override;
};

#endif
