#ifndef QUACK_QUACK_H
#define QUACK_QUACK_H

#include "quack/QuackBehavior.h"

// 구상 전략 : 진짜 오리 울음
class Quack : public QuackBehavior {
public:
	void quack() const override;
};

#endif
