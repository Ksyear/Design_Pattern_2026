#include "state/WinnerState.h"

#include <iostream>

WinnerState::WinnerState(GumballMachine& m) : machine_(m) {}

void WinnerState::insertQuarter() {
	std::cout << "  알맹이를 내보내고 있습니다\n";
}

void WinnerState::ejectQuarter() {
	std::cout << "  이미 알맹이를 뽑으셨습니다\n";
}

void WinnerState::turnCrank() {
	std::cout << "  손잡이는 한 번만 돌려 주세요\n";
}

void WinnerState::dispense() {
	std::cout << "  *** 축하합니다! 알맹이를 하나 더 받으실 수 있습니다 ***\n";
	machine_.releaseBall();
	if (machine_.getCount() == 0) {
		machine_.setState(machine_.getSoldOutState());
		return;
	}
	machine_.releaseBall();
	if (machine_.getCount() > 0) machine_.setState(machine_.getNoQuarterState());
	else {
		std::cout << "  알맹이가 모두 소진되었습니다\n";
		machine_.setState(machine_.getSoldOutState());
	}
}

std::string WinnerState::name() const {
	return "보너스 당첨";
}
