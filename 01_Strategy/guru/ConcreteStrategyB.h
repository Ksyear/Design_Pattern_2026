#ifndef GURU_CONCRETE_STRATEGY_B_H
#define GURU_CONCRETE_STRATEGY_B_H

#include <string>
#include <string_view>

#include "guru/Strategy.h"

namespace guru {

// ConcreteStrategy : 내림차순 정렬
class ConcreteStrategyB : public Strategy {
public:
	std::string doAlgorithm(std::string_view data) const override;
};

}   // namespace guru

#endif
