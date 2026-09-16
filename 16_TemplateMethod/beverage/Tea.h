#ifndef BEVERAGE_TEA_H
#define BEVERAGE_TEA_H

#include "beverage/CaffeineBeverage.h"

// 추상 단계 두 개만 채운다. 순서는 건드릴 수 없다.
class Tea : public CaffeineBeverage {
protected:
	void brew() const override;
	void addCondiments() const override;
};

#endif
