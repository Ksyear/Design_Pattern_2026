#ifndef SERVER_CONTROLLERSERVER_H
#define SERVER_CONTROLLERSERVER_H

#include <memory>
#include <string>

#include "controller/ControllerPlugin.h"
#include "filter/SpeedFilter.h"
#include "msg/Types.h"

class ControllerServer {
public:
	ControllerServer(std::string robotName,
	                 std::unique_ptr<ControllerPlugin> plugin,
	                 std::unique_ptr<SpeedFilter> filter);

	Twist controlLoop(const Pose2D& pose,
	                  const Pose2D& goal,
	                  const LaserScan& scan,
	                  const Twist& odom) const;

	void setPlugin(std::unique_ptr<ControllerPlugin> plugin);
	void setSpeedFilter(std::unique_ptr<SpeedFilter> filter);

	const std::string& robotName() const;

private:
	void publishCmdVel(const Twist& cmd) const;

	std::unique_ptr<ControllerPlugin> plugin_;
	std::unique_ptr<SpeedFilter> filter_;
	std::string robotName_;
};

#endif
