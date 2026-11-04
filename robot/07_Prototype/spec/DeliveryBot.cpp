#include "spec/DeliveryBot.h"

DeliveryBot::DeliveryBot()
	: RobotSpec("AMR-200", {"2d_lidar", "depth_camera", "imu"}, 0.8)
{
}

std::unique_ptr<RobotSpec> DeliveryBot::clone() const
{
	// 복사 생성자를 호출하는 한 줄. new 하는 쪽이 자기 타입을 알기 때문에
	// 무엇을 만들지 if 로 따질 필요가 없다 - 이것이 프로토타입의 이득이다.
	return std::unique_ptr<RobotSpec>(new DeliveryBot(*this));
}

std::string DeliveryBot::role() const
{
	return "배송";
}
