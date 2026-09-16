// 템플릿 메소드 패턴 (Template Method) - 헤드 퍼스트 8장 커피와 홍차
//
// 이 파일은 "조립과 호출"만 한다. 클래스는 기능별 폴더에 나뉘어 있다.
//   beverage/  음료 - CaffeineBeverage.*(골격) + Coffee/Tea/CoffeeWithHook
//
// 참여자가 한 계층뿐이라 폴더도 하나다. 대신 파일을 열면
// "골격은 .cpp 에 고정되어 있고 서브클래스는 단계만 채운다"가 눈에 바로 들어온다.
//
// 템플릿 메소드의 다른 얼굴 : std::sort 는 '정렬 알고리즘'이라는 골격을 쥐고
// 비교 단계만 우리에게 넘긴다. (단, 상속이 아니라 함수 객체로 넘긴다 -> 전략 패턴에 가깝다)
#include <iostream>
#include <string>

#include "beverage/Coffee.h"
#include "beverage/CoffeeWithHook.h"
#include "beverage/Tea.h"

struct Duck {
	std::string name;
	int weight;
};

int main() {
	std::cout << "=== 홍차 만들기 ===\n";
	Tea tea;
	tea.prepareRecipe();

	std::cout << "=== 커피 만들기 ===\n";
	Coffee coffee;
	coffee.prepareRecipe();

	std::cout << "=== 후크로 첨가물 건너뛰기 ===\n";
	CoffeeWithHook plain(false);
	plain.prepareRecipe();

	std::cout << "=== 후크가 참일 때 ===\n";
	CoffeeWithHook sweet(true);
	sweet.prepareRecipe();

	return 0;
}
