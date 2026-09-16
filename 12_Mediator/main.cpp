// 중재자 패턴 (Mediator) - 헤드 퍼스트 14장 자동화 주택
//
// 이 파일은 "조립과 호출"만 한다. 클래스는 기능별 폴더에 나뉘어 있다.
//   appliance/  가전   - Appliance.*(공통) + Alarm/CoffeePot/Sprinkler/Calendar
//   mediator/   중재자 - Mediator.h(인터페이스) + HomeMediator.*(규칙 전부)
//
// appliance/ 안의 클래스들은 서로를 include 하지 않는다. 그게 이 패턴의 성과다.
// 반대로 mediator/ 는 가전을 전부 알아야 한다 - 복잡도가 사라진 게 아니라 한곳에 모인 것.
#include <iostream>

#include "appliance/Alarm.h"
#include "appliance/Calendar.h"
#include "appliance/CoffeePot.h"
#include "appliance/Sprinkler.h"
#include "mediator/HomeMediator.h"

int main() {
	Alarm alarm;
	CoffeePot coffee;
	Sprinkler sprinkler;
	Calendar calendar;
	HomeMediator mediator(alarm, coffee, sprinkler, calendar);

	std::cout << "--- 평일 + 분리수거 날 ---\n";
	calendar.setDay(/*weekend=*/false, /*trashDay=*/true);
	alarm.ring();

	std::cout << "\n--- 주말 ---\n";
	calendar.setDay(/*weekend=*/true, /*trashDay=*/false);
	alarm.ring();

	// 새 규칙이 생겨도 가전 클래스는 하나도 안 건드린다 - 중재자만 고치면 된다
	return 0;
}
