#ifndef BRINGUP_ROBOTBRINGUP_H
#define BRINGUP_ROBOTBRINGUP_H

#include <memory>
#include <string>

#include "factory/PartsFactory.h"
#include "platform/RobotPlatform.h"

class RobotBringup {
public:
	RobotBringup(std::string site, std::unique_ptr<PartsFactory> parts);
	virtual ~RobotBringup() = default;

	std::unique_ptr<RobotPlatform> launch(const std::string& mission) const;

protected:
	virtual std::unique_ptr<RobotPlatform> createRobot(const std::string& mission) const = 0;

private:
	std::string site_;
	std::unique_ptr<PartsFactory> parts_;
};

#endif
