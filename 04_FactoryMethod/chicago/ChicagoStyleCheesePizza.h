#ifndef CHICAGO_CHICAGO_STYLE_CHEESE_PIZZA_H
#define CHICAGO_CHICAGO_STYLE_CHEESE_PIZZA_H

#include "pizza/Pizza.h"

// ConcreteProduct : 시카고 스타일
class ChicagoStyleCheesePizza : public Pizza {
public:
	ChicagoStyleCheesePizza();
	// 시카고 피자는 네모나게 자른다 - 알고리즘 일부만 바꾼다
	void cut() const override;
};

#endif
