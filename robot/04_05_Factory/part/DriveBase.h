#ifndef PART_DRIVEBASE_H
#define PART_DRIVEBASE_H

#include <string>

class DriveBase {
public:
	virtual ~DriveBase() = default;
	virtual std::string spec() const = 0;
	virtual bool canRotateInPlace() const = 0;
	virtual void onConfigure() = 0;
};

#endif
