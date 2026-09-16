#include "guru/ClientCode.h"

#include <iostream>
#include <memory>

#include "guru/ConcreteStrategyA.h"
#include "guru/ConcreteStrategyB.h"
#include "guru/Context.h"

namespace guru {

void clientCode() {
	Context context(std::make_unique<ConcreteStrategyA>());
	std::cout << "  Client: 전략을 '오름차순 정렬'로 설정했습니다\n";
	context.doSomeBusinessLogic();

	std::cout << "\n  Client: 전략을 '내림차순 정렬'로 바꿉니다\n";
	context.setStrategy(std::make_unique<ConcreteStrategyB>());
	context.doSomeBusinessLogic();
}

}   // namespace guru
