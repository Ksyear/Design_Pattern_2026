// 프로토타입 패턴 (Prototype) - 헤드 퍼스트 14장 몬스터 생성
//
// 이 파일은 "조립과 호출"만 한다. 클래스는 기능별 폴더에 나뉘어 있다.
//   monster/   복제 대상 - Monster.h(clone 인터페이스) + 구상 몬스터 3종
//   registry/  등록소    - MonsterRegistry.*(키 -> 프로토타입)
//
// registry/ 는 Monster 인터페이스만 알고 구상 몬스터를 하나도 모른다.
// 그래서 몬스터를 추가해도 registry/ 는 다시 컴파일할 필요조차 없다.
#include <iostream>
#include <memory>
#include <vector>

#include "monster/Dragon.h"
#include "monster/PlayerGeneratedMonster.h"
#include "monster/Slime.h"
#include "registry/MonsterRegistry.h"

int main() {
	MonsterRegistry registry;
	registry.registerPrototype("dragon", std::make_unique<Dragon>());
	registry.registerPrototype("slime", std::make_unique<Slime>());
	registry.registerPrototype(
		"custom",
		std::make_unique<PlayerGeneratedMonster>("물속 괴수", 220,
		                                         std::vector<std::string>{"소용돌이", "물대포"}));

	// 클라이언트 코드에 구상 클래스 이름이 하나도 없다
	for (const char* key : {"dragon", "slime", "custom", "dragon"}) {
		auto m = registry.create(key);
		if (m) m->describe();
	}

	std::cout << "\n--- 복제본은 원본과 독립적이다 ---\n";
	auto a = registry.create("dragon");
	auto b = registry.create("dragon");
	b->setName("고대 드래곤");
	b->addSkill("공포의 포효");
	a->describe();
	b->describe();

	return 0;
}
