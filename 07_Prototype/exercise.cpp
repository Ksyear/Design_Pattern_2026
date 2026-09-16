// [연습] 프로토타입 패턴 - 얕은 복사가 물어뜯는 순간
//
// 아래처럼 몬스터가 '장비'를 포인터로 들고 있다고 하자.
//
//   struct Weapon { std::string name; int damage; };
//   class Monster { std::shared_ptr<Weapon> weapon_; ... };
//
// TODO 1. clone()을 복사 생성자 기본 동작(= shared_ptr 공유)으로 두고,
//         복제본의 무기 이름을 바꿨을 때 원본까지 바뀌는지 확인할 것 (얕은 복사의 함정)
// TODO 2. deepClone()을 따로 만들어 Weapon까지 새로 할당하도록 고칠 것
// TODO 3. 몬스터끼리 서로를 참조하는 관계(예: leader_ 포인터)를 넣고
//         순환 참조가 있는 객체를 복제할 때 무한 재귀에 빠지지 않게 하려면
//         어떤 장치가 필요한지 정리해 볼 것
//         (힌트: 원본 포인터 -> 복제본 포인터 맵을 들고 다니며 재방문을 막는다)
//
// 정리
//   - refactoring.guru가 말하는 프로토타입의 유일한 단점이 바로 이 '순환 참조 복제'다

#include <iostream>

int main() {
	std::cout << "TODO: 얕은 복사와 깊은 복사의 차이를 직접 확인해 보세요\n";
	return 0;
}
