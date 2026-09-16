// 팩토리 메소드 패턴 (Factory Method) - 헤드 퍼스트 4장 피자 가게 프레임워크
//
// 이 파일은 "조립과 호출"만 한다. 클래스는 기능별 폴더에 나뉘어 있다.
//   pizza/    Product      - Pizza.*(공통 피자)
//   store/    Creator      - PizzaStore.*(주문 흐름 + 팩토리 메소드 선언)
//   ny/       뉴욕 지점    - 구상 피자 2개 + NYPizzaStore
//   chicago/  시카고 지점  - 구상 피자 2개 + ChicagoPizzaStore
//
// 지점을 폴더로 갈라 두면 "새 지점을 낸다 = 폴더 하나를 더 만든다"가 된다.
// store/ 와 pizza/ 는 ny/ 도 chicago/ 도 모른다 -> 확장에 열려 있고 변경에 닫혀 있다.
#include <iostream>

#include "chicago/ChicagoPizzaStore.h"
#include "ny/NYPizzaStore.h"

int main() {
	NYPizzaStore nyStore;
	ChicagoPizzaStore chicagoStore;

	std::cout << "== 에단이 주문한 피자 ==\n";
	nyStore.orderPizza("cheese");

	std::cout << "== 조엘이 주문한 피자 ==\n";
	chicagoStore.orderPizza("cheese");

	std::cout << "== 조개 피자 비교 ==\n";
	nyStore.orderPizza("clam");
	chicagoStore.orderPizza("clam");

	return 0;
}
