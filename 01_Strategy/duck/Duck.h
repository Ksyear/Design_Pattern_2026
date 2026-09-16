#ifndef DUCK_DUCK_H
#define DUCK_DUCK_H

#include <memory>
#include <string>

#include "fly/FlyBehavior.h"
#include "quack/QuackBehavior.h"

// Context : 전략을 들고 위임만 한다.
//
// 핵심: 달라지는 부분(나는 행동, 꽥꽥 행동)을 인터페이스 뒤로 뽑아내고
//       Duck 은 그 인터페이스에 "구성(has-a)"으로 연결한다.
//       -> 상속으로 행동을 물려받는 대신 실행 중에 갈아끼울 수 있다.
//
// 불변식(invariant): 전략 둘은 "항상 존재한다".
//   생성자에서 받고(생성자 주입), 세터에서도 nullptr 을 거부하므로
//   performFly() 안에 if (flyBehavior_) 같은 방어 코드가 필요 없다.
//   책(자바)은 필드를 protected 로 열어 두고 서브클래스가 대입하지만,
//   그러면 "전략이 없는 오리"가 잠시 존재할 수 있어 불변식이 깨진다.
class Duck {
public:
	Duck(std::string name,
	     std::unique_ptr<FlyBehavior> flyBehavior,
	     std::unique_ptr<QuackBehavior> quackBehavior);
	virtual ~Duck() = default;

	virtual void display() const = 0;

	// 직접 구현하지 않고 전략 객체에 위임 -> performXxx 라는 이름을 쓰는 이유
	void performFly() const;
	void performQuack() const;
	void swim() const;

	// 세터가 있기 때문에 "실행 중에" 행동을 바꿀 수 있다 (상속으로는 불가능).
	// nullptr 을 넘기면 std::invalid_argument 를 던진다 - 불변식을 지키기 위해서.
	void setFlyBehavior(std::unique_ptr<FlyBehavior> fb);
	void setQuackBehavior(std::unique_ptr<QuackBehavior> qb);

	const std::string& name() const;

private:
	// protected 가 아니라 private : 서브클래스도 직접 건드릴 수 없다
	std::unique_ptr<FlyBehavior> flyBehavior_;
	std::unique_ptr<QuackBehavior> quackBehavior_;
	std::string name_;
};

#endif
