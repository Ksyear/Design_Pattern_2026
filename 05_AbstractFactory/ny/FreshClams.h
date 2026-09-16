#ifndef NY_FRESH_CLAMS_H
#define NY_FRESH_CLAMS_H

#include "ingredient/Clams.h"

// Concrete Product : 뉴욕 제품군의 Clams
class FreshClams : public Clams {
public:
	std::string name() const override;
};

#endif
