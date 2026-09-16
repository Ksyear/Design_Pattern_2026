#ifndef DUCK_MALLARD_DUCK_H
#define DUCK_MALLARD_DUCK_H

#include "duck/Duck.h"

// 구상 Context : 어떤 전략을 기본값으로 들고 시작할지만 정한다.
// 헤더는 Duck 만 알면 된다 -> 어떤 구상 전략을 쓰는지는 .cpp 안에 숨는다.
class MallardDuck : public Duck {
public:
	MallardDuck();
	void display() const override;
};

#endif
