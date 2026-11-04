#include "director/MissionDirector.h"

#include "builder/MissionBuilder.h"

Mission MissionDirector::nightPatrol(const std::string& robotId)
{
	// 야간 순찰 : 천천히, 무한 반복, 막히면 제자리 회전 후 재시도
	return MissionBuilder(robotId)
		.waypoint("로비", 0.0, 0.0)
		.waypoint("복도끝", 12.0, 0.0)
		.waypoint("창고문", 12.0, 8.0)
		.speedLimit(0.35)
		.recovery("spin")
		.recovery("wait")
		.loopForever()
		.build();
}

Mission MissionDirector::packageDelivery(const std::string& robotId, double dropX, double dropY)
{
	// 배송 : 집품대 -> 목적지 -> 충전 도크, 한 번만
	return MissionBuilder(robotId)
		.waypoint("집품대", 2.0, 1.0)
		.waypoint("배송지", dropX, dropY)
		.waypoint("충전도크", 0.0, 0.0)
		.speedLimit(0.6)
		.recovery("backup")
		.recovery("clear_costmap")
		.build();
}
