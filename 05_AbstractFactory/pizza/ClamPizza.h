#ifndef PIZZA_CLAM_PIZZA_H
#define PIZZA_CLAM_PIZZA_H

#include "pizza/Pizza.h"

class ClamPizza : public Pizza {
public:
	using Pizza::Pizza;
	void prepare() override;
};

#endif
