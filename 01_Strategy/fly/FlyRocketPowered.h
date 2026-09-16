#ifndef FLY_FLY_ROCKET_POWERED_H
#define FLY_FLY_ROCKET_POWERED_H

#include "fly/FlyBehavior.h"

// 구상 전략 : 실행 중에 끼워 넣어 보는 전략
class FlyRocketPowered : public FlyBehavior {
public:
	void fly() const override;
};

#endif
