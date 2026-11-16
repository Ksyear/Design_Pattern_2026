#include "device/MobileBase.h"

#include <cmath>
#include <iomanip>
#include <iostream>

namespace {
constexpr double kDegToRad = 3.14159265358979323846 / 180.0;
}

void MobileBase::driveForward(double meters)
{
	x_ += meters * std::cos(headingDeg_ * kDegToRad);
	y_ += meters * std::sin(headingDeg_ * kDegToRad);
	std::cout << "      [base] " << std::showpos << std::fixed << std::setprecision(2)
	          << meters << "m 주행\n" << std::noshowpos;
}

void MobileBase::turn(double degrees)
{
	headingDeg_ += degrees;
	std::cout << "      [base] " << std::showpos << std::fixed << std::setprecision(1)
	          << degrees << "도 회전\n" << std::noshowpos;
}

void MobileBase::report() const
{
	std::cout << "    현재 위치 (" << std::fixed << std::setprecision(2) << x_ << ", " << y_
	          << ")  방위 " << std::setprecision(1) << headingDeg_ << "도\n";
}
