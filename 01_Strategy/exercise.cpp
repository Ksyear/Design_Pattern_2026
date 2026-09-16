// [연습] 전략 패턴 - 헤드 퍼스트 1장 '해야 할 일' 액션 어드벤처 게임
//
// 조건
//   - 캐릭터: King, Queen, Knight, Troll
//   - 무기  : KnifeBehavior, BowAndArrowBehavior, AxeBehavior, SwordBehavior
//   - 캐릭터는 한 번에 무기 하나만 들 수 있고, 게임 도중 무기를 바꿀 수 있다
//
// TODO 1. WeaponBehavior 인터페이스를 만들고 useWeapon()을 선언
// TODO 2. 무기 4개를 구상 클래스로 구현
// TODO 3. Character를 Context로 만들고 WeaponBehavior를 구성으로 들고 있게 할 것
//         - fight()는 무기에 위임만 한다
//         - setWeapon()으로 실행 중에 교체 가능해야 한다
// TODO 4. main에서 Knight가 칼을 들었다가 도끼로 바꾸는 장면을 출력

#include <iostream>

int main() {
	std::cout << "TODO: 전략 패턴으로 캐릭터/무기를 분리해 보세요\n";
	std::cout << "정답 힌트: main.cpp의 Duck <-> FlyBehavior 관계를 그대로 옮기면 됩니다\n";
	return 0;
}
