#include "device/Gripper.h"

#include <iostream>

void Gripper::open()
{
	closed_ = false;
	std::cout << "      [gripper] 열림\n";
}

void Gripper::close()
{
	closed_ = true;
	std::cout << "      [gripper] 닫힘 (파지)\n";
}

bool Gripper::isClosed() const
{
	return closed_;
}
