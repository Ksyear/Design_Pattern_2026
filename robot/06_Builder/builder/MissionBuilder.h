#ifndef BUILDER_MISSIONBUILDER_H
#define BUILDER_MISSIONBUILDER_H

#include <string>
#include <vector>

#include "mission/Mission.h"
#include "mission/Waypoint.h"

// Builder - 임무를 한 조각씩 쌓아 올린다.
//
// 생성자 인자 다섯 개짜리 Mission 을 직접 부르는 것과 뭐가 다른가?
//   Mission("r1", {...}, 0.4, {"spin", "backup"}, true)
// 이 호출은 1년 뒤에 읽으면 0.4 가 뭔지, true 가 뭔지 알 수 없다.
// 게다가 경유지는 보통 조건에 따라 하나씩 붙는다 (충전소 들를지, 검수대 거칠지).
// 그 "조건에 따라 하나씩" 이 빌더가 필요한 진짜 이유다.
//
// 각 메소드가 자기 참조를 돌려주기 때문에 점으로 이어 쓸 수 있다 (메소드 체이닝).
class MissionBuilder {
public:
	explicit MissionBuilder(std::string robotId);

	MissionBuilder& waypoint(const std::string& label, double x, double y);
	MissionBuilder& speedLimit(double metersPerSecond);
	MissionBuilder& recovery(const std::string& behavior);
	MissionBuilder& loopForever();

	// 여기서 비로소 완성품이 나온다. 경유지가 없으면 거부한다.
	Mission build() const;

private:
	std::string robotId_;
	std::vector<Waypoint> waypoints_;
	double speedLimit_ = 0.5;
	std::vector<std::string> recoveries_;
	bool looping_ = false;
};

#endif
