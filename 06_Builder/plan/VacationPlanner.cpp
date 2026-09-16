#include "plan/VacationPlanner.h"

#include <iostream>
#include <utility>

void VacationPlanner::addDay(DayPlan d) {
	days_.push_back(std::move(d));
}

void VacationPlanner::print() const {
	std::cout << "===== 휴가 계획표 =====\n";
	for (const auto& d : days_) {
		std::cout << d.day << "일차\n";
		if (!d.hotel.empty()) std::cout << "  숙박: " << d.hotel << '\n';
		for (const auto& t : d.tickets)      std::cout << "  입장권: " << t << '\n';
		for (const auto& r : d.reservations) std::cout << "  예약: " << r << '\n';
		for (const auto& e : d.specialEvents) std::cout << "  이벤트: " << e << '\n';
	}
	std::cout << '\n';
}
