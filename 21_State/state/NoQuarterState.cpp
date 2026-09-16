#include "state/NoQuarterState.h"

#include <iostream>

NoQuarterState::NoQuarterState(GumballMachine& m) : machine_(m) {}

void NoQuarterState::insertQuarter() {
	std::cout << "  동전을 넣으셨습니다\n";
	machine_.setState(machine_.getHasQuarterState());   // 상태가 전이를 결정한다
}

void NoQuarterState::ejectQuarter() {
	std::cout << "  동전을 넣어 주세요\n";
}

void NoQuarterState::turnCrank() {
	std::cout << "  동전을 넣어 주세요\n";
}

void NoQuarterState::dispense() {
	std::cout << "  동전을 넣어 주세요\n";
}

std::string NoQuarterState::name() const {
	return "동전 투입 대기 중";
}
