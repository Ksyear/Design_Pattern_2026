// [연습] 싱글턴 패턴 - 테스트 가능성이라는 진짜 대가
//
// refactoring.guru가 지적하는 싱글턴의 단점 중 가장 실무적인 것은
// "단위 테스트를 어렵게 만든다"이다. 직접 겪어 보자.
//
// 시나리오
//   Logger가 싱글턴이고, OrderService가 Logger::getInstance()를 직접 호출한다.
//
// TODO 1. 위 구조를 그대로 만들고, OrderService의 로그 출력만 검증하는 테스트를 짜 볼 것
//         -> 로거를 가짜(mock)로 바꿀 방법이 없어 막힌다는 점을 확인
// TODO 2. OrderService가 ILogger& 를 생성자로 주입받도록 고칠 것 (의존성 주입)
//         -> Logger 싱글턴은 그대로 두고, main에서만 getInstance()를 넘긴다
// TODO 3. 테스트에서 FakeLogger를 넘겨 출력 내용을 검증할 것
//
// 정리
//   싱글턴의 문제는 '인스턴스가 하나'인 것이 아니라
//   '어디서든 몰래 꺼내 쓸 수 있다(global access point)'는 쪽에 있다.
//   생명주기는 싱글턴에 맡기되, 의존은 인터페이스로 주입받는 것이 절충안이다.

#include <iostream>

int main() {
	std::cout << "TODO: 싱글턴 로거를 주입 가능한 구조로 바꿔 보세요\n";
	return 0;
}
