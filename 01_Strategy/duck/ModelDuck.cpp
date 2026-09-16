#include "duck/ModelDuck.h"

#include <iostream>
#include <memory>

#include "fly/FlyNoWay.h"
#include "quack/Quack.h"

// 기본 전략은 '기반 클래스 생성자에 넘기는 인자'일 뿐이다.
// 몸통에서 대입하지 않으므로 전략이 비어 있는 순간이 아예 없다.
ModelDuck::ModelDuck()
	: Duck("모형 오리",
	     // 모형이라 못 난다
	       std::make_unique<FlyNoWay>(),
	       std::make_unique<Quack>()) {}

void ModelDuck::display() const {
	std::cout << "[모형 오리] 모습을 보여 줍니다\n";
}
