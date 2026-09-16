#ifndef FLY_FLY_BEHAVIOR_H
#define FLY_FLY_BEHAVIOR_H

// 전략 인터페이스 : 달라지는 부분(나는 행동)을 캡슐화한다.
// Duck 은 이 타입만 알고, 어떤 구상 클래스가 들어오는지는 모른다.
class FlyBehavior {
public:
	virtual ~FlyBehavior() = default;
	virtual void fly() const = 0;
};

#endif
