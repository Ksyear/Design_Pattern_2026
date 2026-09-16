#ifndef BUILDER_PATTERN_LAND_BUILDER_H
#define BUILDER_PATTERN_LAND_BUILDER_H

#include <memory>
#include <string>

#include "builder/AbstractBuilder.h"
#include "plan/DayPlan.h"

// ConcreteBuilder
// 미완성 제품을 밖에 노출하지 않는다 - 다 쌓은 뒤 getVacationPlanner() 로만 꺼낸다.
class PatternLandBuilder : public AbstractBuilder {
public:
	AbstractBuilder& buildDay(int day) override;
	AbstractBuilder& addHotel(const std::string& hotel) override;
	AbstractBuilder& addTickets(const std::string& event) override;
	AbstractBuilder& addReservation(const std::string& restaurant) override;
	AbstractBuilder& addSpecialEvent(const std::string& event) override;

	std::unique_ptr<VacationPlanner> getVacationPlanner() override;

private:
	void requireDay();
	void flushCurrentDay();

	std::unique_ptr<VacationPlanner> planner_ = std::make_unique<VacationPlanner>();
	DayPlan current_;
	bool hasDay_ = false;
};

#endif
