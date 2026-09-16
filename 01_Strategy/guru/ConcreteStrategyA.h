#ifndef GURU_CONCRETE_STRATEGY_A_H
#define GURU_CONCRETE_STRATEGY_A_H

#include <string>
#include <string_view>

#include "guru/Strategy.h"

namespace guru {

// ConcreteStrategy : 오름차순 정렬
class ConcreteStrategyA : public Strategy {
public:
	std::string doAlgorithm(std::string_view data) const override;
};

}   // namespace guru

#endif
