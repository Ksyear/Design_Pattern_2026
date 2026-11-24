#include "subsystem/LidarDriver.h"

#include <iostream>

void LidarDriver::spinUp()
{
	std::cout << "    [lidar] 스핀 업 (10Hz 도달까지 3초)\n";
}

void LidarDriver::spinDown()
{
	std::cout << "    [lidar] 스핀 다운\n";
}
