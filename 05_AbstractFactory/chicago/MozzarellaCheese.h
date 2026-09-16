#ifndef CHICAGO_MOZZARELLA_CHEESE_H
#define CHICAGO_MOZZARELLA_CHEESE_H

#include "ingredient/Cheese.h"

// Concrete Product : 시카고 제품군의 Cheese
class MozzarellaCheese : public Cheese {
public:
	std::string name() const override;
};

#endif
