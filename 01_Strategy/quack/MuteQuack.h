#ifndef QUACK_MUTE_QUACK_H
#define QUACK_MUTE_QUACK_H

#include "quack/QuackBehavior.h"

// 구상 전략 : 소리를 내지 않는다 - Null Object 역할
class MuteQuack : public QuackBehavior {
public:
	void quack() const override;
};

#endif
