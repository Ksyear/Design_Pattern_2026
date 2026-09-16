// 반복자 패턴 (Iterator) - 헤드 퍼스트 9장 객체마을 식당 + 팬케이크 하우스 합병
//
// 이 파일은 "조립과 호출"만 한다. 클래스는 기능별 폴더에 나뉘어 있다.
//   menu/      집합체 - MenuItem.h, Menu.h(인터페이스), DinerMenu/PancakeHouseMenu/CafeMenu
//   iterator/  반복   - Iterator.h(인터페이스) + 컬렉션별 구상 반복자
//   waitress/  Client - Waitress.*(컬렉션 종류를 모른다)
//
// 폴더가 갈린 덕분에 "항목 관리(menu/)와 반복(iterator/)은 다른 책임"이라는
// 단일 역할 원칙이 파일 배치로 드러난다.
#include <iostream>

#include "menu/CafeMenu.h"
#include "menu/DinerMenu.h"
#include "menu/MenuItem.h"
#include "menu/PancakeHouseMenu.h"
#include "waitress/Waitress.h"

int main() {
	PancakeHouseMenu pancakeHouseMenu;
	DinerMenu dinerMenu;

	Waitress waitress({&pancakeHouseMenu, &dinerMenu});
	waitress.printMenu();
	std::cout << '\n';
	waitress.printVegetarianMenu();

	std::cout << "\n== 카페 메뉴 (STL 반복자 + 범위 기반 for) ==\n";
	CafeMenu cafeMenu;
	for (const MenuItem& item : cafeMenu) {
		std::cout << "  " << item.name << " ($" << item.price << ")\n";
	}

	// 반복자를 두 개 동시에 돌릴 수 있다 - 각자 자기 위치를 따로 기억한다
	std::cout << "\n== 반복자 두 개를 동시에 ==\n";
	auto a = dinerMenu.createIterator();
	auto b = dinerMenu.createIterator();
	a->next();
	std::cout << "  a의 두 번째: " << a->next().name << '\n';
	std::cout << "  b의 첫 번째: " << b->next().name << '\n';

	return 0;
}
