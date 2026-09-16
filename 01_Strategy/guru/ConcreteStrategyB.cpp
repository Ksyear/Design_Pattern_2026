#include "guru/ConcreteStrategyB.h"

#include <algorithm>
#include <functional>

namespace guru {

std::string ConcreteStrategyB::doAlgorithm(std::string_view data) const {
	std::string result(data);
	std::sort(result.begin(), result.end(), std::greater<char>());
	return result;
}

}   // namespace guru
