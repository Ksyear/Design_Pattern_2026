#include "chicago/ChicagoStyleClamPizza.h"

#include <iostream>

ChicagoStyleClamPizza::ChicagoStyleClamPizza()
	: Pizza("시카고 스타일 조개 피자",
	        {"잘게 조각낸 모짜렐라 치즈", "냉동 조개"}) {}

void ChicagoStyleClamPizza::cut() const {
	std::cout << "  네모난 모양으로 피자 자르기\n";
}
