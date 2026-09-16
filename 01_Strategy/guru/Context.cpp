#include "guru/Context.h"

#include <iostream>
#include <string>
#include <utility>

namespace guru {

Context::Context(std::unique_ptr<Strategy> strategy) : strategy_(std::move(strategy)) {}

void Context::setStrategy(std::unique_ptr<Strategy> strategy) {
	strategy_ = std::move(strategy);
}

void Context::doSomeBusinessLogic() const {
	if (!strategy_) {
		std::cout << "  Context: 전략이 없습니다\n";
		return;
	}
	std::cout << "  Context: 데이터를 정렬합니다 (어떻게 정렬되는지는 모릅니다)\n";
	const std::string result = strategy_->doAlgorithm("aecbd");
	std::cout << "  결과: " << result << '\n';
}

}   // namespace guru
