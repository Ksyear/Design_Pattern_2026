#ifndef FLY_FLY_WITH_WINGS_H
#define FLY_FLY_WITH_WINGS_H

#include "fly/FlyBehavior.h"

// 구상 전략 : 날개로 나는 기본 구현
class FlyWithWings : public FlyBehavior {
public:
	void fly() const override;
};

#endif
