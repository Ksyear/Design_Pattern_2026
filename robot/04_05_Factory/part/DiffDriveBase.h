#ifndef PART_DIFFDRIVEBASE_H
#define PART_DIFFDRIVEBASE_H

#include "part/DriveBase.h"

class DiffDriveBase : public DriveBase {
public:
	std::string spec() const override;
	bool canRotateInPlace() const override;
	void onConfigure() override;
};

#endif
