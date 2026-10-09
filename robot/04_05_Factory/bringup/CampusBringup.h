#ifndef BRINGUP_CAMPUSBRINGUP_H
#define BRINGUP_CAMPUSBRINGUP_H

#include "bringup/RobotBringup.h"

class CampusBringup : public RobotBringup {
public:
	CampusBringup();

protected:
	std::unique_ptr<RobotPlatform> createRobot(const std::string& mission) const override;
};

#endif
