#ifndef STORE_PIZZA_STORE_H
#define STORE_PIZZA_STORE_H

#include <memory>
#include <string>

#include "pizza/Pizza.h"

// Creator
//
// 핵심: 생성자(Creator)가 "무엇을 만들지"는 서브클래스가 결정한다.
//       orderPizza() 는 절대 바뀌지 않고(= 알고리즘 고정),
//       createPizza() 만 서브클래스에서 재정의된다.
//
// 주의: 피자를 만드는 일은 PizzaStore 의 '주된' 책임이 아니다.
//       주된 책임은 주문 처리 흐름이고, 생성은 그 흐름에 끼워 넣는 훅이다.
class PizzaStore {
public:
	virtual ~PizzaStore() = default;

	// 이 메소드는 서브클래스에서 건드리지 않는다 (템플릿 메소드 성격)
	std::unique_ptr<Pizza> orderPizza(const std::string& type);

protected:
	// 팩토리 메소드 : "어떤 클래스의 인스턴스를 만들지는 서브클래스가 결정한다"
	virtual std::unique_ptr<Pizza> createPizza(const std::string& type) = 0;
};

#endif
