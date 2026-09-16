#include "beverage/HouseBlend.h"

// 설명을 기반 클래스 생성자에 넘긴다 - 몸통에서 대입하지 않는다
HouseBlend::HouseBlend() : Beverage("하우스 블렌드 커피") {}

double HouseBlend::cost() const {
	return 0.89;
}
