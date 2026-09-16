#ifndef BEVERAGE_ESPRESSO_H
#define BEVERAGE_ESPRESSO_H

#include "beverage/Beverage.h"

// ConcreteComponent : 아무것도 감싸지 않은 기본 음료
class Espresso : public Beverage {
public:
	Espresso();
	double cost() const override;
};

#endif
