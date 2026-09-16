#ifndef CHICAGO_FROZEN_CLAMS_H
#define CHICAGO_FROZEN_CLAMS_H

#include "ingredient/Clams.h"

// Concrete Product : 시카고 제품군의 Clams
class FrozenClams : public Clams {
public:
	std::string name() const override;
};

#endif
