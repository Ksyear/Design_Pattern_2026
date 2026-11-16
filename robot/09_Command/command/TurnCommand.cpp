#include "command/TurnCommand.h"

#include <stdexcept>

TurnCommand::TurnCommand(MobileBase* base, double degrees)
	: base_(base), degrees_(degrees)
{
	if (base_ == nullptr) {
		throw std::invalid_argument("TurnCommand 에 장치가 필요합니다");
	}
}

void TurnCommand::execute()
{
	base_->turn(degrees_);
}

void TurnCommand::undo()
{
	base_->turn(-degrees_);
}

std::string TurnCommand::name() const
{
	return "회전";
}
