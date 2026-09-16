#include "mediator/HomeMediator.h"

#include <iostream>
#include <vector>

HomeMediator::HomeMediator(Alarm& a, CoffeePot& c, Sprinkler& s, Calendar& cal)
	: alarm_(a), coffee_(c), sprinkler_(s), calendar_(cal) {
	for (Appliance* p : std::vector<Appliance*>{&a, &c, &s, &cal}) p->setMediator(this);
}

void HomeMediator::notify(Appliance* sender, const std::string& event) {
	if (event == "alarm_off" && sender == &alarm_) {
		std::cout << "중재자: '알람 해제' 이벤트 수신 -> 규칙 적용\n";

		// 규칙 1. 주말에는 커피를 내리지 않는다
		if (calendar_.isWeekend()) coffee_.doAction("skip");
		else                       coffee_.doAction("brew");

		// 규칙 2. 샤워 예정 시각 15분 전에는 스프링클러를 끈다
		sprinkler_.doAction("off");

		// 규칙 3. 분리수거 날이면 다음 알람을 앞당긴다
		if (calendar_.isTrashDay()) alarm_.doAction("advance");
	}
}
