#ifndef SPEC_DELIVERYBOT_H
#define SPEC_DELIVERYBOT_H

#include "spec/RobotSpec.h"

class DeliveryBot : public RobotSpec {
public:
	DeliveryBot();

	std::unique_ptr<RobotSpec> clone() const override;
	std::string role() const override;
};

#endif
