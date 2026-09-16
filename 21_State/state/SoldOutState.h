#ifndef STATE_SOLD_OUT_STATE_H
#define STATE_SOLD_OUT_STATE_H

#include <string>

#include "machine/GumballMachine.h"
#include "state/State.h"

// ConcreteState : 자기 상태에서의 행동만 안다. 다음 상태로 넘기는 것도 자기 책임.
class SoldOutState : public State {
public:
	explicit SoldOutState(GumballMachine& m);

	void insertQuarter() override;
	void ejectQuarter() override;
	void turnCrank() override;
	void dispense() override;
	std::string name() const override;

private:
	GumballMachine& machine_;
};

#endif
