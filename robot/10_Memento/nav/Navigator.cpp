#include "nav/Navigator.h"

#include <iomanip>
#include <iostream>
#include <utility>

Navigator::Snapshot::Snapshot(std::string label, double x, double y, double yaw,
                              int waypointIndex, double battery)
	: label_(std::move(label)), x_(x), y_(y), yaw_(yaw),
	  waypointIndex_(waypointIndex), battery_(battery)
{
}

const std::string& Navigator::Snapshot::label() const
{
	return label_;
}

Navigator::Navigator(double x, double y, double yaw)
	: x_(x), y_(y), yaw_(yaw)
{
}

void Navigator::driveTo(double x, double y, double yaw, double batteryCost)
{
	x_ = x;
	y_ = y;
	yaw_ = yaw;
	battery_ -= batteryCost;
	std::cout << "    주행 -> (" << std::fixed << std::setprecision(1) << x_ << ", " << y_ << ")\n";
}

void Navigator::reachWaypoint()
{
	++waypointIndex_;
	std::cout << "    경유지 " << waypointIndex_ << " 도달\n";
}

void Navigator::report() const
{
	std::cout << "  [상태] 위치 (" << std::fixed << std::setprecision(1) << x_ << ", " << y_
	          << ")  방위 " << yaw_ << "  경유지 " << waypointIndex_
	          << "  배터리 " << std::setprecision(0) << (battery_ * 100.0) << "%\n";
}

Navigator::Snapshot Navigator::save(std::string label) const
{
	// 스냅샷을 만들 수 있는 것은 자기 자신뿐이다
	return Snapshot(std::move(label), x_, y_, yaw_, waypointIndex_, battery_);
}

void Navigator::restore(const Snapshot& snapshot)
{
	x_ = snapshot.x_;      // friend 라서 private 멤버에 손이 닿는다
	y_ = snapshot.y_;
	yaw_ = snapshot.yaw_;
	waypointIndex_ = snapshot.waypointIndex_;
	battery_ = snapshot.battery_;
	std::cout << "    체크포인트 '" << snapshot.label_ << "' 로 복원\n";
}
