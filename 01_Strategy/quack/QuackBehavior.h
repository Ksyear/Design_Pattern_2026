#ifndef QUACK_QUACK_BEHAVIOR_H
#define QUACK_QUACK_BEHAVIOR_H

// 전략 인터페이스 : 달라지는 부분(꽥꽥 행동)을 캡슐화한다.
class QuackBehavior {
public:
	virtual ~QuackBehavior() = default;
	virtual void quack() const = 0;
};

#endif
