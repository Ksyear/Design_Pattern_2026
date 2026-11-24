#ifndef FACADE_AUTONOMYFACADE_H
#define FACADE_AUTONOMYFACADE_H

#include "subsystem/LidarDriver.h"
#include "subsystem/Localization.h"
#include "subsystem/MotorDriver.h"
#include "subsystem/NavStack.h"
#include "subsystem/PowerRail.h"

// Facade - 복잡한 시동 절차에 문 하나를 달아 준다.
//
// 감추는 것은 "순서" 다. 전원 -> 모터 -> 브레이크 -> 라이다 -> 측위 -> 내비.
// 이 순서를 틀리면 브레이크가 걸린 채로 주행하거나, 수렴 전에 목표를 받는다.
// 순서를 아는 곳이 여러 군데면 언젠가 한 곳이 틀린다.
//
// 파사드는 하위 시스템을 "숨기지" 않는다. 막지도 않는다.
// 필요하면 아래 장치를 직접 꺼내 쓸 수 있어야 한다 (캘리브레이션, 정비 모드).
// 그래서 게터를 열어 두었다 - 이것이 파사드와 어댑터의 차이이기도 하다.
//   어댑터 : 형식을 바꾼다 (기능은 그대로)
//   파사드 : 쓰기 쉽게 한다 (형식은 그대로, 조합만 제공)
class AutonomyFacade {
public:
	// 한 줄로 자율주행 준비 완료
	bool startAutonomy(const char* mapName, double initX, double initY);

	// 끌 때는 역순이다. 이것도 파사드가 안다.
	void shutdown();

	// 정비용 - 하위 시스템 직접 접근
	MotorDriver& motors();

private:
	PowerRail power_;
	MotorDriver motors_;
	LidarDriver lidar_;
	Localization localization_;
	NavStack nav_;
	bool navActive_ = false;  // 켠 것만 끈다 - configure 전의 nav2 에 deactivate 를 보내지 않는다
};

#endif
