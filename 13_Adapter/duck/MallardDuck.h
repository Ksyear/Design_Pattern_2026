#ifndef DUCK_MALLARD_DUCK_H
#define DUCK_MALLARD_DUCK_H

#include "duck/Duck.h"

// 진짜 Target 구현 - 비교용
class MallardDuck : public Duck {
public:
	void quack() const override;
	void fly() const override;
};

#endif
