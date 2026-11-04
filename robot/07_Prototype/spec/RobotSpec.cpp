#include "spec/RobotSpec.h"

#include <iomanip>
#include <iostream>
#include <utility>

RobotSpec::RobotSpec(std::string model, std::vector<std::string> sensors, double maxSpeed)
	: model_(std::move(model)), sensors_(std::move(sensors)), maxSpeed_(maxSpeed)
{
}

void RobotSpec::placeAt(std::string namespaceName, double x, double y)
{
	namespace_ = std::move(namespaceName);
	x_ = x;
	y_ = y;
}

void RobotSpec::addSensor(const std::string& sensor)
{
	sensors_.push_back(sensor);
}

void RobotSpec::describe() const
{
	std::cout << "  /" << namespace_ << "  " << model_ << " [" << role() << "]"
	          << "  at (" << std::fixed << std::setprecision(1) << x_ << ", " << y_ << ")"
	          << "  max " << std::setprecision(2) << maxSpeed_ << " m/s\n";
	std::cout << "      센서 :";
	for (const std::string& s : sensors_) {
		std::cout << ' ' << s;
	}
	std::cout << '\n';
}
