#ifndef CONDIMENT_WHIP_H
#define CONDIMENT_WHIP_H

#include "condiment/CondimentDecorator.h"

// ConcreteDecorator : 감싼 음료에게 물어본 뒤 자기 몫을 더한다
class Whip : public CondimentDecorator {
public:
	using CondimentDecorator::CondimentDecorator;

	std::string getDescription() const override;
	double cost() const override;
};

#endif
