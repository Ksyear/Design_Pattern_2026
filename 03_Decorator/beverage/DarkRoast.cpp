#include "beverage/DarkRoast.h"

// 설명을 기반 클래스 생성자에 넘긴다 - 몸통에서 대입하지 않는다
DarkRoast::DarkRoast() : Beverage("다크 로스트 커피") {}

double DarkRoast::cost() const {
	return 0.99;
}
