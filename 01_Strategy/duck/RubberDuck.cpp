#include "duck/RubberDuck.h"

#include <iostream>
#include <memory>

#include "fly/FlyNoWay.h"
#include "quack/Squeak.h"

// 기본 전략은 '기반 클래스 생성자에 넘기는 인자'일 뿐이다.
// 몸통에서 대입하지 않으므로 전략이 비어 있는 순간이 아예 없다.
RubberDuck::RubberDuck()
	: Duck("고무 오리",
	       std::make_unique<FlyNoWay>(),
	       std::make_unique<Squeak>()) {}

void RubberDuck::display() const {
	std::cout << "[고무 오리] 모습을 보여 줍니다\n";
}
