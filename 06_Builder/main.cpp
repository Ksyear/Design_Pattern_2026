// 빌더 패턴 (Builder) - 헤드 퍼스트 14장 패턴랜드 휴가 계획표
//
// 이 파일은 "조립과 호출"만 한다. 클래스는 기능별 폴더에 나뉘어 있다.
//   plan/      Product    - DayPlan.h(부품) + VacationPlanner.*(완성품)
//   builder/   조립 단계  - AbstractBuilder.h(인터페이스) + PatternLandBuilder.*
//   director/  조립 순서  - VacationDirector.*
//
// '무엇을 만드는가(plan)'와 '어떻게 쌓는가(builder)'와 '어떤 순서로 쌓는가(director)'가
// 폴더 세 개로 갈린다. 이 셋이 서로 독립이라는 점이 빌더 패턴의 전부다.
#include <iostream>

#include "builder/PatternLandBuilder.h"
#include "director/VacationDirector.h"

int main() {
	PatternLandBuilder builder;

	std::cout << "[객체마을 주민] 호텔 없이 저녁과 이벤트만\n";
	VacationDirector::localResidentPlan(builder)->print();

	std::cout << "[관광객] 3박 전체 코스\n";
	VacationDirector::touristPlan(builder)->print();

	// Director 없이 클라이언트가 직접 단계를 고를 수도 있다
	std::cout << "[직접 조립] 하루짜리 즉흥 여행\n";
	builder.buildDay(1).addTickets("프록시 동물원").addReservation("팬케이크 하우스");
	builder.getVacationPlanner()->print();

	return 0;
}
