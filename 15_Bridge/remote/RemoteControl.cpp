#include "remote/RemoteControl.h"

#include <iostream>
#include <utility>

RemoteControl::RemoteControl(std::unique_ptr<TV> tv) : tv_(std::move(tv)) {}

void RemoteControl::on() {
	tv_->on();
}

void RemoteControl::off() {
	tv_->off();
}

void RemoteControl::setChannel(int channel) {
	channel_ = channel;
	tv_->tuneChannel(channel_);
}

void RemoteControl::nextChannel() {
	setChannel(channel_ + 1);
}

void RemoteControl::previousChannel() {
	setChannel(channel_ - 1);
}

void RemoteControl::setTV(std::unique_ptr<TV> tv) {
	tv_ = std::move(tv);
	std::cout << "리모컨을 " << tv_->brand() << " TV에 연결했습니다\n";
}
