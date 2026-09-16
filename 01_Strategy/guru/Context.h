#ifndef GURU_CONTEXT_H
#define GURU_CONTEXT_H

#include <memory>

#include "guru/Strategy.h"

namespace guru {

// Context : 전략을 소유하고(unique_ptr) 위임만 한다.
//
// duck/Duck.h 와 비교
//   - 전략이 하나뿐이라 필드도 하나. Duck 은 fly/quack 두 축을 들고 있다
//   - 생성자에서 전략을 받는다(생성자 주입) -> "전략 없는 Context" 가 만들어지지 않는다
//     Duck 은 protected 필드에 서브클래스가 직접 대입하는 방식이라 이 보장이 없다
class Context {
public:
	explicit Context(std::unique_ptr<Strategy> strategy = nullptr);

	// 실행 중 교체 - 전략 패턴의 핵심
	void setStrategy(std::unique_ptr<Strategy> strategy);

	// Context 는 '무엇을' 할지만 알고 '어떻게' 는 모른다
	void doSomeBusinessLogic() const;

private:
	std::unique_ptr<Strategy> strategy_;
};

}   // namespace guru

#endif
