#ifndef STATE_STATE_H
#define STATE_STATE_H

#include <string>

// State 인터페이스
//
// 핵심: 상태마다 클래스를 하나씩 만들고, Context 는 현재 상태 객체에 일을 위임한다.
//       거대한 if/switch 덩어리가 사라지고, 상태가 늘어도 기존 코드를 안 건드린다.
//
// 전략 패턴과 구조가 똑같지만 의도가 다르다
//   - 전략: 클라이언트가 알고리즘을 골라 넣는다. 전략끼리는 서로 모른다
//   - 상태: 상태 객체가 스스로 다음 상태를 정한다. 상태끼리 서로 안다
//   즉 전이(transition)의 주체가 누구냐가 갈림길이다.
class State {
public:
	virtual ~State() = default;
	virtual void insertQuarter() = 0;
	virtual void ejectQuarter() = 0;
	virtual void turnCrank() = 0;
	virtual void dispense() = 0;
	virtual std::string name() const = 0;
};

#endif
