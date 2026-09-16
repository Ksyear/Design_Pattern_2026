#ifndef BUILDER_ABSTRACT_BUILDER_H
#define BUILDER_ABSTRACT_BUILDER_H

#include <memory>
#include <string>

#include "plan/VacationPlanner.h"

// Builder 인터페이스 : 조립 '단계'를 선언한다.
//
// 핵심: 복합 객체를 '여러 단계'에 걸쳐 만든다.
//       팩토리는 한 번의 호출로 완성품을 돌려주지만, 빌더는 단계를 나눠 쌓는다.
//       -> 손님마다 다른 계획표(호텔만, 입장권만, 전부 다)를 같은 코드로 만들 수 있다.
class AbstractBuilder {
public:
	virtual ~AbstractBuilder() = default;
	virtual AbstractBuilder& buildDay(int day) = 0;
	virtual AbstractBuilder& addHotel(const std::string& hotel) = 0;
	virtual AbstractBuilder& addTickets(const std::string& event) = 0;
	virtual AbstractBuilder& addReservation(const std::string& restaurant) = 0;
	virtual AbstractBuilder& addSpecialEvent(const std::string& event) = 0;
	virtual std::unique_ptr<VacationPlanner> getVacationPlanner() = 0;
};

#endif
