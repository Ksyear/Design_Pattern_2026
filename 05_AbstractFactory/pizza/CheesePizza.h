#ifndef PIZZA_CHEESE_PIZZA_H
#define PIZZA_CHEESE_PIZZA_H

#include "pizza/Pizza.h"

// 같은 CheesePizza 클래스인데도 공장이 다르면 재료군 전체가 통째로 달라진다
class CheesePizza : public Pizza {
public:
	using Pizza::Pizza;
	void prepare() override;
};

#endif
