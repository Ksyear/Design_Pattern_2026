#include "adapter/TurkeyAdapter.h"

#include <utility>

TurkeyAdapter::TurkeyAdapter(std::shared_ptr<Turkey> turkey) : turkey_(std::move(turkey)) {}

void TurkeyAdapter::quack() const {
	turkey_->gobble();
}

// 칠면조는 짧게 나니까 다섯 번 날려서 오리 흉내를 낸다 - 이게 '번역'
void TurkeyAdapter::fly() const {
	for (int i = 0; i < 5; ++i) turkey_->fly();
}
