#include "state/HasQuarterState.h"

#include <cstdlib>
#include <iostream>

HasQuarterState::HasQuarterState(GumballMachine& m) : machine_(m) {}

void HasQuarterState::insertQuarter() {
	std::cout << "  동전은 한 개만 넣어 주세요\n";
}

void HasQuarterState::ejectQuarter() {
	std::cout << "  동전이 반환됩니다\n";
	machine_.setState(machine_.getNoQuarterState());
}

void HasQuarterState::turnCrank() {
	std::cout << "  손잡이를 돌리셨습니다\n";
	// 10% 확률로 보너스 - 상태를 하나 추가해도 다른 상태 클래스는 안 바뀐다
	if (std::rand() % 10 == 0 && machine_.getCount() > 1) {
		machine_.setState(machine_.getWinnerState());
	} else {
		machine_.setState(machine_.getSoldState());
	}
}

void HasQuarterState::dispense() {
	std::cout << "  알맹이가 나갈 수 없습니다\n";
}

std::string HasQuarterState::name() const {
	return "동전 있음";
}
