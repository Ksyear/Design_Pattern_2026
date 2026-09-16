// 데코레이터 패턴 (Decorator) - 헤드 퍼스트 3장 스타버즈 커피
//
// 이 파일은 "조립과 호출"만 한다. 클래스는 기능별 폴더에 나뉘어 있다.
//   beverage/   음료 본체   - Beverage.h(Component) + 구상 음료 3개
//   condiment/  첨가물 기능 - CondimentDecorator.*(추상) + 구상 첨가물 3개
//
// 핵심: 데코레이터는 자기가 감쌀 구성 요소와 "같은 인터페이스"를 구현한다.
//       -> 감싼 결과물도 여전히 Beverage 이므로 몇 겹이든 다시 감쌀 수 있다.
// 폴더로 보면 condiment/ 는 beverage/ 를 알지만 beverage/ 는 condiment/ 를 모른다.
#include <iomanip>
#include <iostream>
#include <memory>

#include "beverage/DarkRoast.h"
#include "beverage/Espresso.h"
#include "beverage/HouseBlend.h"
#include "condiment/Mocha.h"
#include "condiment/Soy.h"
#include "condiment/Whip.h"

static void printOrder(const Beverage& b) {
	std::cout << b.getDescription() << " $" << std::fixed << std::setprecision(2) << b.cost()
	          << std::defaultfloat << '\n';
}

int main() {
	// 아무것도 안 씌운 에스프레소
	auto beverage1 = std::make_unique<Espresso>();
	printOrder(*beverage1);

	// 다크 로스트 + 모카 두 번 + 휘핑크림
	std::unique_ptr<Beverage> beverage2 = std::make_unique<DarkRoast>();
	beverage2 = std::make_unique<Mocha>(std::move(beverage2));
	beverage2 = std::make_unique<Mocha>(std::move(beverage2));   // 같은 첨가물을 두 번 얹을 수 있다
	beverage2 = std::make_unique<Whip>(std::move(beverage2));
	printOrder(*beverage2);

	// 하우스 블렌드 + 두유 + 모카 + 휘핑크림 (벤티 사이즈)
	std::unique_ptr<Beverage> beverage3 = std::make_unique<HouseBlend>();
	beverage3->setSize(Beverage::Size::Venti);
	beverage3 = std::make_unique<Soy>(std::move(beverage3));
	beverage3 = std::make_unique<Mocha>(std::move(beverage3));
	beverage3 = std::make_unique<Whip>(std::move(beverage3));
	printOrder(*beverage3);

	return 0;
}
