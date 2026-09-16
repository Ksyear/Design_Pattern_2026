#include "state/SoldState.h"

#include <iostream>

SoldState::SoldState(GumballMachine& m) : machine_(m) {}

void SoldState::insertQuarter() {
	std::cout << "  알맹이를 내보내고 있습니다\n";
}

void SoldState::ejectQuarter() {
	std::cout << "  이미 알맹이를 뽑으셨습니다\n";
}

void SoldState::turnCrank() {
	std::cout << "  손잡이는 한 번만 돌려 주세요\n";
}

void SoldState::dispense() {
	machine_.releaseBall();
	if (machine_.getCount() > 0) machine_.setState(machine_.getNoQuarterState());
	else {
		std::cout << "  알맹이가 모두 소진되었습니다\n";
		machine_.setState(machine_.getSoldOutState());
	}
}

std::string SoldState::name() const {
	return "알맹이 배출 중";
}
