#include "guru/ConcreteStrategyA.h"

#include <algorithm>

namespace guru {

std::string ConcreteStrategyA::doAlgorithm(std::string_view data) const {
	std::string result(data);
	std::sort(result.begin(), result.end());
	return result;
}

}   // namespace guru
