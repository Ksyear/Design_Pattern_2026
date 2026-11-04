#ifndef SPEC_PATROLBOT_H
#define SPEC_PATROLBOT_H

#include "spec/RobotSpec.h"

class PatrolBot : public RobotSpec {
public:
	PatrolBot();

	std::unique_ptr<RobotSpec> clone() const override;
	std::string role() const override;
};

#endif
