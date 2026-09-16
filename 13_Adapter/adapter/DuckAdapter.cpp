#include "adapter/DuckAdapter.h"

#include <utility>

DuckAdapter::DuckAdapter(std::shared_ptr<Duck> duck) : duck_(std::move(duck)) {}

void DuckAdapter::gobble() const {
	duck_->quack();
}

void DuckAdapter::fly() const {
	duck_->fly();
}
