#ifndef CONDIMENT_MOCHA_H
#define CONDIMENT_MOCHA_H

#include "condiment/CondimentDecorator.h"

// ConcreteDecorator : 감싼 음료에게 물어본 뒤 자기 몫을 더한다
class Mocha : public CondimentDecorator {
public:
	using CondimentDecorator::CondimentDecorator;

	std::string getDescription() const override;
	double cost() const override;
};

#endif
