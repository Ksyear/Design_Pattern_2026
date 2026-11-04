#ifndef MISSION_MISSION_H
#define MISSION_MISSION_H

#include <string>
#include <vector>

#include "mission/Waypoint.h"

// Product - 완성된 내비게이션 임무.
//
// 완성된 다음에는 바꿀 수 없게 게터만 열어 두었다.
// "짓는 동안" 과 "다 지어진 다음" 을 분리하는 것이 빌더의 목적이다.
// 실제로 임무를 절반만 채운 채로 nav2 에 넘기면 로봇이 이상한 곳으로 간다.
class Mission {
public:
	Mission(std::string robotId,
	        std::vector<Waypoint> waypoints,
	        double speedLimit,
	        std::vector<std::string> recoveries,
	        bool looping);

	void print() const;

	const std::vector<Waypoint>& waypoints() const;

private:
	std::string robotId_;
	std::vector<Waypoint> waypoints_;
	double speedLimit_;
	std::vector<std::string> recoveries_;
	bool looping_;
};

#endif
