#ifndef CHICAGO_PLUM_TOMATO_SAUCE_H
#define CHICAGO_PLUM_TOMATO_SAUCE_H

#include "ingredient/Sauce.h"

// Concrete Product : 시카고 제품군의 Sauce
class PlumTomatoSauce : public Sauce {
public:
	std::string name() const override;
};

#endif
