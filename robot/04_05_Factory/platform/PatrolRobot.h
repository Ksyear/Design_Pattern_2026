#ifndef PLATFORM_PATROLROBOT_H
#define PLATFORM_PATROLROBOT_H

#include <memory>

#include "platform/RobotPlatform.h"

class PatrolRobot : public RobotPlatform {
public:
	using RobotPlatform::RobotPlatform;

	void assemble(const PartsFactory& parts) override;
	void printBom() const override;

private:
	std::unique_ptr<Camera> camera_;
};

#endif
