#include "duck/Duck.h"

#include <iostream>
#include <stdexcept>
#include <utility>

Duck::Duck(std::string name,
           std::unique_ptr<FlyBehavior> flyBehavior,
           std::unique_ptr<QuackBehavior> quackBehavior)
	: flyBehavior_(std::move(flyBehavior)),
	  quackBehavior_(std::move(quackBehavior)),
	  name_(std::move(name)) {
	// 여기서 한 번 막으면 이후 모든 메소드가 "전략은 있다"를 전제할 수 있다
	if (!flyBehavior_) throw std::invalid_argument("Duck: flyBehavior 가 nullptr 입니다");
	if (!quackBehavior_) throw std::invalid_argument("Duck: quackBehavior 가 nullptr 입니다");
}

void Duck::performFly() const {
	flyBehavior_->fly();
}

void Duck::performQuack() const {
	quackBehavior_->quack();
}

void Duck::swim() const {
	std::cout << "  모든 오리는 물에 뜹니다\n";
}

void Duck::setFlyBehavior(std::unique_ptr<FlyBehavior> fb) {
	if (!fb) throw std::invalid_argument("setFlyBehavior: nullptr 은 받을 수 없습니다");
	flyBehavior_ = std::move(fb);
}

void Duck::setQuackBehavior(std::unique_ptr<QuackBehavior> qb) {
	if (!qb) throw std::invalid_argument("setQuackBehavior: nullptr 은 받을 수 없습니다");
	quackBehavior_ = std::move(qb);
}

const std::string& Duck::name() const {
	return name_;
}
