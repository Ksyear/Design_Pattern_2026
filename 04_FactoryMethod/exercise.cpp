// [연습] 팩토리 메소드 패턴 - 헤드 퍼스트 4장 캘리포니아 피자 가게
//
// TODO 1. CAStyleCheesePizza / CAStyleVeggiePizza 를 만들 것
//         (토핑에 "말린 토마토", "아보카도" 같은 재료를 넣어 캘리포니아답게)
// TODO 2. CaliforniaPizzaStore를 PizzaStore 서브클래스로 만들고 createPizza를 재정의
// TODO 3. PizzaStore::orderPizza 코드를 한 글자도 고치지 않고 새 가게가 동작하는지 확인 (OCP)
//
// 생각해 볼 것
//   - '간단한 팩토리(Simple Factory)'와 팩토리 메소드의 차이는?
//     간단한 팩토리는 생성을 한 객체에 몰아넣은 관용구(idiom)일 뿐 상속으로 확장하지 않는다
//   - createPizza에 if/else가 그대로 남아 있는데, 이건 나쁜 코드인가?
//     -> 조건문이 '가게마다 한 군데'로 모였다는 점이 핵심. 클라이언트에는 조건문이 없다

#include <iostream>

int main() {
	std::cout << "TODO: 캘리포니아 피자 가게를 추가해 보세요\n";
	return 0;
}
