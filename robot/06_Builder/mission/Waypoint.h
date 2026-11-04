#ifndef MISSION_WAYPOINT_H
#define MISSION_WAYPOINT_H

#include <string>

// nav2_msgs 의 웨이포인트 하나 (geometry_msgs/PoseStamped + 이름표)
struct Waypoint {
	std::string label;
	double x = 0.0;
	double y = 0.0;
};

#endif
