#ifndef PLATFORM_ROBOTPLATFORM_H
#define PLATFORM_ROBOTPLATFORM_H

#include <memory>
#include <string>

#include "factory/PartsFactory.h"

class RobotPlatform {
public:
	explicit RobotPlatform(std::string name);
	virtual ~RobotPlatform() = default;

	virtual void assemble(const PartsFactory& parts) = 0;

	void configure();
	virtual void printBom() const;
	void planPath() const;

	const std::string& name() const;

protected:
	std::unique_ptr<Lidar> lidar_;
	std::unique_ptr<Localizer> localizer_;
	std::unique_ptr<DriveBase> driveBase_;

private:
	std::string name_;
};

#endif
