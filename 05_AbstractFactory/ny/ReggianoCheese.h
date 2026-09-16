#ifndef NY_REGGIANO_CHEESE_H
#define NY_REGGIANO_CHEESE_H

#include "ingredient/Cheese.h"

// Concrete Product : 뉴욕 제품군의 Cheese
class ReggianoCheese : public Cheese {
public:
	std::string name() const override;
};

#endif
