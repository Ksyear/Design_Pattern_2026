#ifndef PART_ACKERMANNBASE_H
#define PART_ACKERMANNBASE_H

#include "part/DriveBase.h"

class AckermannBase : public DriveBase {
public:
	std::string spec() const override;
	bool canRotateInPlace() const override;
	void onConfigure() override;
};

#endif
