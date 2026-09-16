#ifndef CONDIMENT_SOY_H
#define CONDIMENT_SOY_H

#include "condiment/CondimentDecorator.h"

// 사이즈에 따라 값이 달라지는 첨가물 - 책 3장 연습문제.
// 사이즈는 자기가 들고 있지 않고 감싼 음료에게 물어본다.
class Soy : public CondimentDecorator {
public:
	using CondimentDecorator::CondimentDecorator;

	std::string getDescription() const override;
	double cost() const override;
};

#endif
