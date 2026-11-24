#ifndef MSG_LASERSCAN_H
#define MSG_LASERSCAN_H

#include <string>
#include <vector>

// 상위 코드(내비게이션)가 기대하는 표준 형식 - sensor_msgs/msg/LaserScan
struct LaserScan {
	std::string frameId;
	std::vector<double> ranges;  // m 단위, 측정 실패는 0.0
};

#endif
