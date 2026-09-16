#include "director/VacationDirector.h"

std::unique_ptr<VacationPlanner> VacationDirector::localResidentPlan(AbstractBuilder& b) {
	b.buildDay(1).addReservation("객체마을 식당").addSpecialEvent("패턴 온 아이스");
	return b.getVacationPlanner();
}

std::unique_ptr<VacationPlanner> VacationDirector::touristPlan(AbstractBuilder& b) {
	b.buildDay(1).addHotel("그랜드 퍼사디안").addTickets("패턴랜드 종일권");
	b.buildDay(2).addHotel("그랜드 퍼사디안").addReservation("객체마을 식당")
	             .addSpecialEvent("패턴 온 아이스");
	b.buildDay(3).addTickets("싱글턴 박물관");
	return b.getVacationPlanner();
}
