#ifndef BEVERAGE_DARK_ROAST_H
#define BEVERAGE_DARK_ROAST_H

#include "beverage/Beverage.h"

// ConcreteComponent : 아무것도 감싸지 않은 기본 음료
class DarkRoast : public Beverage {
public:
	DarkRoast();
	double cost() const override;
};

#endif
