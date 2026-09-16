// 추상 팩토리 패턴 (Abstract Factory) - 헤드 퍼스트 4장 피자 원재료 공장
//
// 이 파일은 "조립과 호출"만 한다. 클래스는 기능별 폴더에 나뉘어 있다.
//   ingredient/  추상 재료   - Dough/Sauce/Cheese/Clams 인터페이스
//   factory/     추상 공장   - PizzaIngredientFactory.h
//   pizza/       제품        - Pizza.*(재료를 공장에 주문) + CheesePizza/ClamPizza
//   store/       주문 흐름   - PizzaStore.*
//   ny/          뉴욕 제품군   - 구상 재료 4개 + 구상 공장 + 지점
//   chicago/     시카고 제품군 - 구상 재료 4개 + 구상 공장 + 지점
//
// "제품군 = 폴더"라는 점이 이 패턴의 핵심을 그대로 보여 준다.
// ny/ 와 chicago/ 는 서로를 모르고, 재료를 섞어 쓰는 일이 구조적으로 불가능하다.
#include "chicago/ChicagoPizzaStore.h"
#include "ny/NYPizzaStore.h"

int main() {
	NYPizzaStore nyStore;
	ChicagoPizzaStore chicagoStore;

	nyStore.orderPizza("cheese");
	chicagoStore.orderPizza("cheese");
	nyStore.orderPizza("clam");
	chicagoStore.orderPizza("clam");

	return 0;
}
