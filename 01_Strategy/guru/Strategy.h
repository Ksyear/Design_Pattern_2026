#ifndef GURU_STRATEGY_H
#define GURU_STRATEGY_H

#include <string>
#include <string_view>

// refactoring.guru 의 C++ 예제를 이 저장소 규약(.h/.cpp 분리)에 맞춰 옮긴 것.
// 같은 패턴을 GoF 교과서 형태로 쓰면 어떻게 되는지 비교하려고 둔다.
//
// duck/ 쪽과 다른 점
//   - 전략이 값을 '반환'한다 (void + cout 이 아니라 std::string)
//     -> 테스트가 쉽다. 표준 출력이 아니라 반환값을 검사하면 되기 때문
//   - 이름이 도메인 언어가 아니라 패턴 용어다 (Strategy/Context/ConcreteStrategyA)
namespace guru {

class Strategy {
public:
	virtual ~Strategy() = default;

	// const 이고 멤버 상태가 없다 -> 이 전략 객체는 여러 Context 가 공유해도 안전하다
	virtual std::string doAlgorithm(std::string_view data) const = 0;
};

}   // namespace guru

#endif
