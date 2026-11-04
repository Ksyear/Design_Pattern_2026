#ifndef DIRECTOR_MISSIONDIRECTOR_H
#define DIRECTOR_MISSIONDIRECTOR_H

#include <string>

#include "mission/Mission.h"

// Director - 자주 쓰는 임무 조립 순서를 이름으로 굳혀 둔 곳.
//
// 빌더가 "어떻게 쌓을지" 를 알고, 디렉터는 "무엇을 쌓을지" 를 안다.
// 디렉터 없이 빌더만 써도 되지만, 같은 임무를 여러 곳에서 만들 때
// 조립 순서가 조금씩 달라지는 것을 막아 준다.
class MissionDirector {
public:
	static Mission nightPatrol(const std::string& robotId);
	static Mission packageDelivery(const std::string& robotId, double dropX, double dropY);
};

#endif
