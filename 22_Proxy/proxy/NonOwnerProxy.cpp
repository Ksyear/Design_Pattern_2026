#include "proxy/NonOwnerProxy.h"

#include <stdexcept>
#include <utility>

NonOwnerProxy::NonOwnerProxy(std::shared_ptr<Person> p) : person_(std::move(p)) {}

std::string NonOwnerProxy::getName() const {
	return person_->getName();
}

int NonOwnerProxy::getHotOrNotRating() const {
	return person_->getHotOrNotRating();
}

void NonOwnerProxy::setHotOrNotRating(int rating) {
	person_->setHotOrNotRating(rating);
}

void NonOwnerProxy::setInterests(const std::string&) {
	throw std::runtime_error("다른 사람의 정보는 수정할 수 없습니다");
}
