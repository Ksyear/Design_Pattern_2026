#ifndef BEVERAGE_COFFEE_WITH_HOOK_H
#define BEVERAGE_COFFEE_WITH_HOOK_H

#include "beverage/Coffee.h"

// 후크를 재정의해 알고리즘의 한 갈래를 꺼 버리는 예
class CoffeeWithHook : public Coffee {
public:
	explicit CoffeeWithHook(bool wantsCondiments);

protected:
	bool customerWantsCondiments() const override;

private:
	bool wants_;
};

#endif
