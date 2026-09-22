#ifndef FILTER_EMERGENCYBRAKEFILTER_H
#define FILTER_EMERGENCYBRAKEFILTER_H

#include "filter/SpeedFilter.h"

// 비상 정지 - 컨트롤러가 무엇을 계산했든 0 으로 덮는다.
//
// 생각해 볼 것 : StopController 와 결과가 같다. 그런데 자리가 다르다.
//   StopController        = "어떻게 갈지" 를 바꾼 것    -> 목표를 향한 판단을 포기
//   EmergencyBrakeFilter  = "내보낼지" 를 막은 것       -> 컨트롤러는 계속 계산 중
// 어느 쪽에 둘지는 성능이 아니라 책임 배분의 문제다.
// 실제 로봇에서 하드웨어 E-stop 이 후자에 가깝다 (소프트웨어가 뭘 시키든 전원을 끊는다).
class EmergencyBrakeFilter : public SpeedFilter {
public:
	Twist apply(const Twist& raw) const override;
	std::string name() const override;
};

#endif
