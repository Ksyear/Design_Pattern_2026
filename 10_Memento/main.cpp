// 메멘토 패턴 (Memento) - 헤드 퍼스트 14장 게임 세이브
//
// 이 파일은 "조립과 호출"만 한다. 클래스는 기능별 폴더에 나뉘어 있다.
//   character/  Originator - GameCharacter.*(자기 상태를 스스로 포장/복구) + 중첩 Memento
//   save/       Caretaker  - SaveSlots.*(보관만 한다)
//
// 폴더가 갈려도 save/ 는 메멘토 속을 못 본다. 막는 것은 폴더가 아니라 friend 다.
#include <iostream>
#include <string>

#include "character/GameCharacter.h"
#include "save/SaveSlots.h"

int main() {
	GameCharacter hero("객체마을 용사");
	SaveSlots saves;

	std::cout << "--- 레벨을 올릴 때마다 저장 ---\n";
	hero.show();
	for (int i = 0; i < 3; ++i) {
		hero.levelUp(i == 2 ? "전설의 검" : "강철 검");
		hero.show();
		saves.push(hero.save("레벨 " + std::to_string(i + 2) + " 달성"));
	}
	saves.list();

	std::cout << "\n--- 13층에서 사망 ---\n";
	hero.takeDamage(999);
	hero.show();

	std::cout << "\n--- 마지막 세이브에서 부활 ---\n";
	if (const auto* m = saves.last()) hero.restore(*m);
	hero.show();

	// 케어테이커는 m->level_ 에 접근할 수 없다 (private + friend)
	// -> 캡슐화를 유지한 채 상태만 오간다는 것이 메멘토의 요점
	return 0;
}
