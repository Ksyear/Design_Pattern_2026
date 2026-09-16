#include "builder/PatternLandBuilder.h"

#include <utility>

AbstractBuilder& PatternLandBuilder::buildDay(int day) {
	flushCurrentDay();
	current_.day = day;
	hasDay_ = true;
	return *this;
}

AbstractBuilder& PatternLandBuilder::addHotel(const std::string& hotel) {
	requireDay();
	current_.hotel = hotel;
	return *this;
}

AbstractBuilder& PatternLandBuilder::addTickets(const std::string& event) {
	requireDay();
	current_.tickets.push_back(event);
	return *this;
}

AbstractBuilder& PatternLandBuilder::addReservation(const std::string& restaurant) {
	requireDay();
	current_.reservations.push_back(restaurant);
	return *this;
}

AbstractBuilder& PatternLandBuilder::addSpecialEvent(const std::string& event) {
	requireDay();
	current_.specialEvents.push_back(event);
	return *this;
}

std::unique_ptr<VacationPlanner> PatternLandBuilder::getVacationPlanner() {
	flushCurrentDay();
	auto result = std::move(planner_);
	planner_ = std::make_unique<VacationPlanner>();   // 빌더 재사용 대비 초기화
	return result;
}

void PatternLandBuilder::requireDay() {
	if (!hasDay_) buildDay(1);
}

void PatternLandBuilder::flushCurrentDay() {
	if (hasDay_) {
		planner_->addDay(std::move(current_));
		current_ = DayPlan{};
		hasDay_ = false;
	}
}
