// 비지터 패턴 (Visitor) - 헤드 퍼스트 14장 메뉴 영양 정보
//
// 이 파일은 "구조 조립과 순회 호출"만 한다. 클래스는 기능별 폴더에 나뉘어 있다.
//   element/  객체 구조 - MenuComponent.h + Menu/MenuItem/Ingredient (accept 만 안다)
//   visitor/  연산      - Visitor.h + 구상 비지터 3개
//
// 폴더 두 개의 관계가 이 패턴의 트레이드오프를 그대로 보여 준다.
//   연산을 추가한다 = visitor/ 에 파일 하나 추가, element/ 는 0줄 수정
//   element 를 추가한다 = element/ 에 파일 하나 + visitor/ 의 모든 파일 수정
#include <iostream>
#include <memory>
#include <vector>

#include "element/Ingredient.h"
#include "element/Menu.h"
#include "element/MenuItem.h"
#include "visitor/AllergyVisitor.h"
#include "visitor/HealthRatingVisitor.h"
#include "visitor/NutritionVisitor.h"

int main() {
	auto allMenus = std::make_shared<Menu>("전체 메뉴");
	auto dinerMenu = std::make_shared<Menu>("객체마을 식당");

	dinerMenu->add(std::make_shared<MenuItem>(
		"파스타", std::vector<Ingredient>{{"스파게티 면", 350, 12, 70},
		                                 {"마리나라 소스", 80, 2, 15},
		                                 {"올리브유", 120, 0, 0}}));
	dinerMenu->add(std::make_shared<MenuItem>(
		"베지 버거", std::vector<Ingredient>{{"통밀빵", 180, 6, 34},
		                                    {"콩고기 패티", 150, 18, 9},
		                                    {"상추", 5, 0, 1},
		                                    {"치즈", 110, 7, 1}}));
	allMenus->add(dinerMenu);

	std::cout << "===== 비지터 1: 영양 정보 =====\n";
	NutritionVisitor nutrition;
	allMenus->accept(nutrition);
	nutrition.printTotal();

	std::cout << "\n===== 비지터 2: 건강 등급 (구조 수정 0줄) =====\n";
	HealthRatingVisitor health;
	allMenus->accept(health);
	health.finish();

	std::cout << "\n===== 비지터 3: 알레르기 검사 (또 추가) =====\n";
	AllergyVisitor allergy("치즈");
	allMenus->accept(allergy);

	return 0;
}
