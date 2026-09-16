#ifndef OBSERVER_OBSERVER_H
#define OBSERVER_OBSERVER_H

// 옵저버 인터페이스 : 주제는 이 타입만 알면 된다 -> 느슨한 결합
class Observer {
public:
	virtual ~Observer() = default;
	// 풀(pull) 방식이 아니라 푸시(push) 방식 - 책 2장의 첫 번째 구현
	virtual void update(float temp, float humidity, float pressure) = 0;
};

#endif
