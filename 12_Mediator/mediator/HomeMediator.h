#ifndef MEDIATOR_HOME_MEDIATOR_H
#define MEDIATOR_HOME_MEDIATOR_H

#include <string>

#include "appliance/Alarm.h"
#include "appliance/Calendar.h"
#include "appliance/CoffeePot.h"
#include "appliance/Sprinkler.h"
#include "mediator/Mediator.h"

// ConcreteMediator : 모든 규칙이 여기 한 곳에 모인다.
//
// 대가: 제어 로직이 중재자 한 곳에 모이므로, 설계를 잘못하면 God Object 가 된다.
//       이 헤더가 구상 가전을 전부 include 한다는 점이 그 위험을 눈에 보이게 해 준다.
class HomeMediator : public Mediator {
public:
	HomeMediator(Alarm& a, CoffeePot& c, Sprinkler& s, Calendar& cal);

	void notify(Appliance* sender, const std::string& event) override;

private:
	Alarm& alarm_;
	CoffeePot& coffee_;
	Sprinkler& sprinkler_;
	Calendar& calendar_;
};

#endif
