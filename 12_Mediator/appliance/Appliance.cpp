#include "appliance/Appliance.h"

#include <utility>

#include "mediator/Mediator.h"

Appliance::Appliance(std::string name) : name_(std::move(name)) {}

void Appliance::setMediator(Mediator* m) {
	mediator_ = m;
}

const std::string& Appliance::name() const {
	return name_;
}

void Appliance::notifyMediator(const std::string& event) {
	if (mediator_) mediator_->notify(this, event);
}
