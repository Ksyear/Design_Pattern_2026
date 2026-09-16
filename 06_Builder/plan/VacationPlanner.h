#ifndef PLAN_VACATION_PLANNER_H
#define PLAN_VACATION_PLANNER_H

#include <vector>

#include "plan/DayPlan.h"

// Product : 여러 단계에 걸쳐 쌓아 올린 복합 객체
class VacationPlanner {
public:
	void addDay(DayPlan d);
	void print() const;

private:
	std::vector<DayPlan> days_;
};

#endif
