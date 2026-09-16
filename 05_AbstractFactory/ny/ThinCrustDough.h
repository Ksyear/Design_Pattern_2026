#ifndef NY_THIN_CRUST_DOUGH_H
#define NY_THIN_CRUST_DOUGH_H

#include "ingredient/Dough.h"

// Concrete Product : 뉴욕 제품군의 Dough
class ThinCrustDough : public Dough {
public:
	std::string name() const override;
};

#endif
