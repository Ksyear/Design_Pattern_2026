#ifndef ADAPTER_DUCK_ADAPTER_H
#define ADAPTER_DUCK_ADAPTER_H

#include <memory>

#include "duck/Duck.h"
#include "turkey/Turkey.h"

// 반대 방향 어댑터도 가능하다 - 어느 쪽이 Target 인지는 클라이언트가 정한다
class DuckAdapter : public Turkey {
public:
	explicit DuckAdapter(std::shared_ptr<Duck> duck);

	void gobble() const override;
	void fly() const override;

private:
	std::shared_ptr<Duck> duck_;
};

#endif
