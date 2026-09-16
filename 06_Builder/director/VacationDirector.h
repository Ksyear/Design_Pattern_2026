#ifndef DIRECTOR_VACATION_DIRECTOR_H
#define DIRECTOR_VACATION_DIRECTOR_H

#include <memory>

#include "builder/AbstractBuilder.h"
#include "plan/VacationPlanner.h"

// Director : 조립 '순서'를 캡슐화한다 (선택 사항).
// 같은 빌더로 서로 다른 절차를 돌릴 수 있다는 것이 요점.
class VacationDirector {
public:
	static std::unique_ptr<VacationPlanner> localResidentPlan(AbstractBuilder& b);
	static std::unique_ptr<VacationPlanner> touristPlan(AbstractBuilder& b);
};

#endif
