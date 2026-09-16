#ifndef CONDIMENT_CONDIMENT_DECORATOR_H
#define CONDIMENT_CONDIMENT_DECORATOR_H

#include <memory>

#include "beverage/Beverage.h"

// Decorator (추상)
// Beverage 를 상속하는 이유는 '형식을 맞추기 위해서'지 행동을 물려받기 위해서가 아니다.
// 상속은 컴파일 때 끝나지만, 감싸기는 실행 중에 조립된다.
class CondimentDecorator : public Beverage {
public:
	explicit CondimentDecorator(std::unique_ptr<Beverage> b);

	// 사이즈 질문은 감싼 음료에게 그대로 흘려보낸다
	void setSize(Size s) override;
	Size getSize() const override;

protected:
	std::unique_ptr<Beverage> beverage_;
};

#endif
