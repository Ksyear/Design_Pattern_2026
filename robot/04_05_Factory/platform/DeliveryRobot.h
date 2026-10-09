#ifndef PLATFORM_DELIVERYROBOT_H
#define PLATFORM_DELIVERYROBOT_H

#include "platform/RobotPlatform.h"

class DeliveryRobot : public RobotPlatform {
public:
	using RobotPlatform::RobotPlatform;

	void assemble(const PartsFactory& parts) override;
};

#endif
