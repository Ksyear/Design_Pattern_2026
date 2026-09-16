#ifndef ADAPTER_WILD_TURKEY_CLASS_ADAPTER_H
#define ADAPTER_WILD_TURKEY_CLASS_ADAPTER_H

#include "duck/Duck.h"
#include "turkey/WildTurkey.h"

// 클래스 어댑터 (다중 상속) : C++ 에서만 가능한 변형.
// 어댑티 한 종류에만 묶이는 대신 오버라이드가 쉽다.
// private 상속이라 "WildTurkey 다"가 아니라 "WildTurkey 로 구현된다"는 뜻이 된다.
class WildTurkeyClassAdapter : public Duck, private WildTurkey {
public:
	void quack() const override;
	void fly() const override;
};

#endif
