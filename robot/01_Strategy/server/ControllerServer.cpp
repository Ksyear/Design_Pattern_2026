#include "server/ControllerServer.h"

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <utility>

ControllerServer::ControllerServer(std::string robotName,
                                   std::unique_ptr<ControllerPlugin> plugin,
                                   std::unique_ptr<SpeedFilter> filter)
	: plugin_(std::move(plugin)), filter_(std::move(filter)), robotName_(std::move(robotName))
{
	if (!plugin_) {
		throw std::invalid_argument("ControllerPlugin 은 nullptr 일 수 없습니다");
	}
	if (!filter_) {
		throw std::invalid_argument("SpeedFilter 는 nullptr 일 수 없습니다");
	}
}

void ControllerServer::controlLoop(const Pose2D& pose, const Pose2D& goal, const LaserScan& scan) const
{
	const Twist raw = plugin_->computeVelocity(pose, goal, scan);  // 어떻게 갈지 - 전략 1
	const Twist cmd = filter_->apply(raw);                         // 내보낼지   - 전략 2
	publishCmdVel(cmd);
}

void ControllerServer::setPlugin(std::unique_ptr<ControllerPlugin> plugin)
{
	if (!plugin) {
		throw std::invalid_argument("ControllerPlugin 은 nullptr 일 수 없습니다");
	}
	std::cout << "  [param] FollowPath.plugin : " << plugin_->name() << " -> " << plugin->name() << '\n';
	plugin_ = std::move(plugin);
}

void ControllerServer::setSpeedFilter(std::unique_ptr<SpeedFilter> filter)
{
	if (!filter) {
		throw std::invalid_argument("SpeedFilter 는 nullptr 일 수 없습니다");
	}
	std::cout << "  [param] speed_filter     : " << filter_->name() << " -> " << filter->name() << '\n';
	filter_ = std::move(filter);
}

const std::string& ControllerServer::robotName() const
{
	return robotName_;
}

void ControllerServer::publishCmdVel(const Twist& cmd) const
{
	std::cout << "  [" << robotName_ << "] /cmd_vel  linear.x=" << std::fixed << std::setprecision(2)
	          << std::setw(5) << cmd.linear_x
	          << "  angular.z=" << std::setw(5) << cmd.angular_z
	          << "   (plugin=" << plugin_->name() << ", filter=" << filter_->name() << ")\n";
}
