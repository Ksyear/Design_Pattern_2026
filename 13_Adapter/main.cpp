// 어댑터 패턴 (Adapter) - 헤드 퍼스트 7장 칠면조를 오리로
//
// 이 파일은 "조립과 호출"만 한다. 클래스는 기능별 폴더에 나뉘어 있다.
//   duck/     Target  - Duck.h(기대하는 인터페이스) + MallardDuck.*
//   turkey/   Adaptee - Turkey.h(안 맞는 기존 인터페이스) + WildTurkey.*
//   adapter/  번역기  - 객체 어댑터 / 클래스 어댑터 / 반대 방향 어댑터
//
// duck/ 과 turkey/ 는 서로를 전혀 모른다. 둘을 아는 것은 adapter/ 뿐이다.
#include <iostream>
#include <memory>

#include "adapter/DuckAdapter.h"
#include "adapter/TurkeyAdapter.h"
#include "adapter/WildTurkeyClassAdapter.h"
#include "duck/Duck.h"
#include "duck/MallardDuck.h"
#include "turkey/WildTurkey.h"

// 클라이언트 : Duck만 알고, 안에 뭐가 들었는지 모른다
static void testDuck(const Duck& duck) {
	duck.quack();
	duck.fly();
}

int main() {
	auto duck = std::make_shared<MallardDuck>();
	auto turkey = std::make_shared<WildTurkey>();

	std::cout << "--- 칠면조 본래 모습 ---\n";
	turkey->gobble();
	turkey->fly();

	std::cout << "\n--- 객체 어댑터로 감싼 칠면조 ---\n";
	TurkeyAdapter objectAdapter(turkey);
	testDuck(objectAdapter);

	std::cout << "\n--- 클래스 어댑터(다중 상속) ---\n";
	WildTurkeyClassAdapter classAdapter;
	testDuck(classAdapter);

	std::cout << "\n--- 진짜 오리 (비교용) ---\n";
	testDuck(*duck);

	std::cout << "\n--- 반대 방향: 오리를 칠면조로 ---\n";
	DuckAdapter reverse(duck);
	reverse.gobble();
	reverse.fly();

	return 0;
}
