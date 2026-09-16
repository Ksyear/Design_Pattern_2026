#include "chicago/ChicagoStyleCheesePizza.h"

#include <iostream>

ChicagoStyleCheesePizza::ChicagoStyleCheesePizza()
	: Pizza("시카고 스타일 딥 디쉬 치즈 피자",
	        {"잘게 조각낸 모짜렐라 치즈"}) {}

void ChicagoStyleCheesePizza::cut() const {
	std::cout << "  네모난 모양으로 피자 자르기\n";
}
