// 컴포지트 패턴 (Composite) - 헤드 퍼스트 9장 메뉴 안의 서브메뉴
//
// 이 파일은 "트리 조립과 호출"만 한다. 클래스는 역할별 폴더에 나뉘어 있다.
//   component/  공통 타입 - MenuComponent.*(잎과 노드가 공유하는 인터페이스)
//   leaf/       잎        - MenuItem.*
//   composite/  노드      - Menu.*(자식을 담고 재귀한다)
//
// leaf/ 와 composite/ 는 서로를 모른다. 둘 다 component/ 만 본다.
// 그래서 클라이언트도 둘을 구분하지 않고 print() 하나만 부를 수 있다.
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "composite/Menu.h"
#include "leaf/MenuItem.h"

int main() {
	auto pancakeHouseMenu = std::make_shared<Menu>("팬케이크 하우스 메뉴", "아침 메뉴");
	auto dinerMenu = std::make_shared<Menu>("객체마을 식당 메뉴", "점심 메뉴");
	auto cafeMenu = std::make_shared<Menu>("카페 메뉴", "저녁 메뉴");
	auto dessertMenu = std::make_shared<Menu>("디저트 메뉴", "디저트를 즐겨 보세요");

	auto allMenus = std::make_shared<Menu>("전체 메뉴", "모든 메뉴를 종합한 메뉴");
	allMenus->add(pancakeHouseMenu);
	allMenus->add(dinerMenu);
	allMenus->add(cafeMenu);

	pancakeHouseMenu->add(std::make_shared<MenuItem>(
		"K&B 팬케이크 세트", "스크램블 에그과 토스트가 곁들여진 팬케이크", true, 2.99));
	pancakeHouseMenu->add(std::make_shared<MenuItem>(
		"블루베리 팬케이크", "신선한 블루베리와 블루베리 시럽으로 만든 팬케이크", true, 3.49));

	dinerMenu->add(std::make_shared<MenuItem>("파스타", "마리나라 소스 스파게티, 효모빵도 드립니다", true, 3.89));
	dinerMenu->add(std::make_shared<MenuItem>("핫도그", "사워크라우트, 양념, 양파, 치즈가 곁들여진 핫도그", false, 3.05));

	// 메뉴 안에 메뉴 - 트리의 깊이는 제한이 없다
	dinerMenu->add(dessertMenu);
	dessertMenu->add(std::make_shared<MenuItem>("애플 파이", "바삭한 크러스트에 바닐라 아이스크림이 얹어진 애플 파이", true, 1.59));
	dessertMenu->add(std::make_shared<MenuItem>("치즈 케이크", "초콜릿 그레이엄 크러스트 위에 부드러운 뉴욕 치즈케이크", true, 1.99));

	cafeMenu->add(std::make_shared<MenuItem>("베지 버거와 에어 프라이", "통밀빵, 상추, 토마토, 감자 튀김", true, 3.99));
	cafeMenu->add(std::make_shared<MenuItem>("부리토", "통 핀토콩과 살사, 구아카몰이 들어간 부리토", true, 4.29));

	// 종업원은 최상위 노드 하나에 print()만 부른다
	std::cout << "===== 전체 메뉴 =====\n";
	allMenus->print();

	std::cout << "\n전체 합계: $" << std::fixed << std::setprecision(2) << allMenus->totalPrice()
	          << std::defaultfloat << '\n';

	// 잎에 add를 부르면 예외 - '투명성'을 택한 대가
	std::cout << "\n--- 잎에 add를 시도하면 ---\n";
	try {
		MenuItem leaf("테스트", "설명", false, 0.0);
		leaf.add(nullptr);
	} catch (const std::logic_error& e) {
		std::cout << "  예외: " << e.what() << '\n';
	}

	return 0;
}
