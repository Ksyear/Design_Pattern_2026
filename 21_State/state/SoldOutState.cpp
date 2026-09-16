#include "state/SoldOutState.h"

#include <iostream>

SoldOutState::SoldOutState(GumballMachine& m) : machine_(m) {}

void SoldOutState::insertQuarter() {
	std::cout << "  매진되었습니다 (남은 알맹이 " << machine_.getCount()
	          << "개). 동전을 넣을 수 없습니다\n";
}

void SoldOutState::ejectQuarter() {
	std::cout << "  동전을 넣지 않으셨습니다\n";
}

void SoldOutState::turnCrank() {
	std::cout << "  매진되었습니다\n";
}

void SoldOutState::dispense() {
	std::cout << "  알맹이가 나갈 수 없습니다\n";
}

std::string SoldOutState::name() const {
	return "매진";
}
