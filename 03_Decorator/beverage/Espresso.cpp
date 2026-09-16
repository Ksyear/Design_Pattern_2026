#include "beverage/Espresso.h"

// 설명을 기반 클래스 생성자에 넘긴다 - 몸통에서 대입하지 않는다
Espresso::Espresso() : Beverage("에스프레소") {}

double Espresso::cost() const {
	return 1.99;
}
