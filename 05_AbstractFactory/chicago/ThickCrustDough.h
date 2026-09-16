#ifndef CHICAGO_THICK_CRUST_DOUGH_H
#define CHICAGO_THICK_CRUST_DOUGH_H

#include "ingredient/Dough.h"

// Concrete Product : 시카고 제품군의 Dough
class ThickCrustDough : public Dough {
public:
	std::string name() const override;
};

#endif
