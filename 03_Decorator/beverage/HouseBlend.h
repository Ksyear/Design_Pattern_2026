#ifndef BEVERAGE_HOUSE_BLEND_H
#define BEVERAGE_HOUSE_BLEND_H

#include "beverage/Beverage.h"

// ConcreteComponent : 아무것도 감싸지 않은 기본 음료
class HouseBlend : public Beverage {
public:
	HouseBlend();
	double cost() const override;
};

#endif
