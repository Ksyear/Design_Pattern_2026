#ifndef QUACK_SQUEAK_H
#define QUACK_SQUEAK_H

#include "quack/QuackBehavior.h"

// 구상 전략 : 고무 오리 소리
class Squeak : public QuackBehavior {
public:
	void quack() const override;
};

#endif
