#include "machine/GumballMachine.h"

#include <iostream>

#include "state/HasQuarterState.h"
#include "state/NoQuarterState.h"
#include "state/SoldOutState.h"
#include "state/SoldState.h"
#include "state/WinnerState.h"

GumballMachine::GumballMachine(int numberGumballs) : count_(numberGumballs) {
	soldOutState_ = std::make_unique<SoldOutState>(*this);
	noQuarterState_ = std::make_unique<NoQuarterState>(*this);
	hasQuarterState_ = std::make_unique<HasQuarterState>(*this);
	soldState_ = std::make_unique<SoldState>(*this);
	winnerState_ = std::make_unique<WinnerState>(*this);
	state_ = numberGumballs > 0 ? noQuarterState_.get() : soldOutState_.get();
}

void GumballMachine::insertQuarter() {
	state_->insertQuarter();
}

void GumballMachine::ejectQuarter() {
	state_->ejectQuarter();
}

void GumballMachine::turnCrank() {
	state_->turnCrank();
	state_->dispense();   // 크랭크를 돌리면 배출까지 이어진다
}

void GumballMachine::setState(State* s) {
	state_ = s;
}

void GumballMachine::releaseBall() {
	if (count_ > 0) {
		std::cout << "  알맹이가 나가는 중...\n";
		--count_;
	}
}

int GumballMachine::getCount() const {
	return count_;
}

State* GumballMachine::getSoldOutState() const {
	return soldOutState_.get();
}

State* GumballMachine::getNoQuarterState() const {
	return noQuarterState_.get();
}

State* GumballMachine::getHasQuarterState() const {
	return hasQuarterState_.get();
}

State* GumballMachine::getSoldState() const {
	return soldState_.get();
}

State* GumballMachine::getWinnerState() const {
	return winnerState_.get();
}

void GumballMachine::report() const {
	std::cout << "  [기계 상태] 알맹이 " << count_ << "개 / " << state_->name() << "\n\n";
}
