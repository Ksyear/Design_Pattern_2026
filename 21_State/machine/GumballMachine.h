#ifndef MACHINE_GUMBALL_MACHINE_H
#define MACHINE_GUMBALL_MACHINE_H

#include <memory>

#include "state/State.h"

// Context : 현재 상태 객체에 일을 위임할 뿐 스스로 판단하지 않는다.
// 이 헤더에 if 도 switch 도 없다는 점이 상태 패턴의 성과다.
class GumballMachine {
public:
	explicit GumballMachine(int numberGumballs);

	void insertQuarter();
	void ejectQuarter();
	void turnCrank();

	void setState(State* s);

	// 상태 객체들이 문맥을 조작할 수 있도록 열어 둔다
	void releaseBall();
	int getCount() const;

	State* getSoldOutState() const;
	State* getNoQuarterState() const;
	State* getHasQuarterState() const;
	State* getSoldState() const;
	State* getWinnerState() const;

	void report() const;

private:
	std::unique_ptr<State> soldOutState_;
	std::unique_ptr<State> noQuarterState_;
	std::unique_ptr<State> hasQuarterState_;
	std::unique_ptr<State> soldState_;
	std::unique_ptr<State> winnerState_;

	State* state_ = nullptr;
	int count_ = 0;
};

#endif
