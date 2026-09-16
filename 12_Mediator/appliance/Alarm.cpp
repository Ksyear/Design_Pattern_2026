#include "appliance/Alarm.h"

#include <iostream>

Alarm::Alarm() : Appliance("알람 시계") {}

void Alarm::ring() {
	std::cout << "알람 시계: 울림\n";
	notifyMediator("alarm_off");
}

void Alarm::doAction(const std::string& action) {
	if (action == "advance") std::cout << "  알람 시계: 내일은 15분 일찍 울리도록 설정\n";
}
