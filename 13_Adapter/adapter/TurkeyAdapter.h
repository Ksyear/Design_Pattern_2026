#ifndef ADAPTER_TURKEY_ADAPTER_H
#define ADAPTER_TURKEY_ADAPTER_H

#include <memory>

#include "duck/Duck.h"
#include "turkey/Turkey.h"

// 객체 어댑터 (구성)
//
// 핵심: 클라이언트가 기대하는 인터페이스(Target)로 기존 클래스(Adaptee)를 감싸 번역한다.
//       클라이언트는 어댑터가 끼어든 줄도 모른다.
//
// 구성이라서 Turkey 의 서브클래스 전부에 쓸 수 있다  <- 기본 선택
class TurkeyAdapter : public Duck {
public:
	explicit TurkeyAdapter(std::shared_ptr<Turkey> turkey);

	void quack() const override;
	void fly() const override;

private:
	std::shared_ptr<Turkey> turkey_;
};

#endif
