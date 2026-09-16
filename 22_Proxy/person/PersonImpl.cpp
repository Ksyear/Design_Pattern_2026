#include "person/PersonImpl.h"

#include <utility>

PersonImpl::PersonImpl(std::string name) : name_(std::move(name)) {}

std::string PersonImpl::getName() const {
	return name_;
}

int PersonImpl::getHotOrNotRating() const {
	return ratingCount_ == 0 ? 0 : ratingSum_ / ratingCount_;
}

void PersonImpl::setHotOrNotRating(int rating) {
	ratingSum_ += rating;
	++ratingCount_;
}

void PersonImpl::setInterests(const std::string& interests) {
	interests_ = interests;
}
