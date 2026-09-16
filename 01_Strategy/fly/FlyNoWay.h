#ifndef FLY_FLY_NO_WAY_H
#define FLY_FLY_NO_WAY_H

#include "fly/FlyBehavior.h"

// 구상 전략 : 못 나는 오리용 - Null Object 역할도 겸한다
class FlyNoWay : public FlyBehavior {
public:
	void fly() const override;
};

#endif
