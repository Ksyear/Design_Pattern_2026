#ifndef PLAN_DAY_PLAN_H
#define PLAN_DAY_PLAN_H

#include <string>
#include <vector>

// Product 의 부품 : 하루치 일정.
// 여기에 항목이 늘어도 빌더의 '단계'만 늘리면 되고 조립 코드는 그대로다.
struct DayPlan {
	int day = 0;
	std::string hotel;
	std::vector<std::string> tickets;
	std::vector<std::string> reservations;
	std::vector<std::string> specialEvents;
};

#endif
