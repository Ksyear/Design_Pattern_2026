#include "proxy/OwnerProxy.h"

#include <stdexcept>
#include <utility>

OwnerProxy::OwnerProxy(std::shared_ptr<Person> p) : person_(std::move(p)) {}

std::string OwnerProxy::getName() const {
	return person_->getName();
}

int OwnerProxy::getHotOrNotRating() const {
	return person_->getHotOrNotRating();
}

void OwnerProxy::setInterests(const std::string& interests) {
	person_->setInterests(interests);
}

void OwnerProxy::setHotOrNotRating(int) {
	throw std::runtime_error("본인에게는 점수를 줄 수 없습니다");
}
