#ifndef NY_MARINARA_SAUCE_H
#define NY_MARINARA_SAUCE_H

#include "ingredient/Sauce.h"

// Concrete Product : 뉴욕 제품군의 Sauce
class MarinaraSauce : public Sauce {
public:
	std::string name() const override;
};

#endif
