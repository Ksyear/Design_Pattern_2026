// 상태 패턴 (State) - 헤드 퍼스트 10장 뽑기 기계
//
// 이 파일은 "조립과 호출"만 한다. 클래스는 기능별 폴더에 나뉘어 있다.
//   machine/  Context - GumballMachine.*(위임만 한다, if/switch 없음)
//   state/    상태들  - State.h(인터페이스) + 구상 상태 5개
//
// 상태를 하나 더 만든다 = state/ 에 파일 두 개 추가.
// WinnerState 가 그 예다 - 추가할 때 다른 상태 클래스는 한 줄도 안 바뀌었다.
#include <cstdlib>
#include <iostream>

#include "machine/GumballMachine.h"

int main() {
	std::srand(42);   // 재현 가능한 결과를 위해 고정

	GumballMachine machine(6);
	machine.report();

	machine.insertQuarter();
	machine.turnCrank();
	machine.report();

	machine.insertQuarter();
	machine.ejectQuarter();
	machine.turnCrank();
	machine.report();

	std::cout << "--- 매진될 때까지 반복 ---\n";
	for (int i = 0; i < 8; ++i) {
		machine.insertQuarter();
		machine.turnCrank();
	}
	machine.report();

	return 0;
}
