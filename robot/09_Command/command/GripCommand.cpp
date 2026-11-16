#include "command/GripCommand.h"

#include <stdexcept>

GripCommand::GripCommand(Gripper* gripper, bool shouldClose)
	: gripper_(gripper), shouldClose_(shouldClose)
{
	if (gripper_ == nullptr) {
		throw std::invalid_argument("GripCommand 에 그리퍼가 필요합니다");
	}
}

void GripCommand::execute()
{
	previousClosed_ = gripper_->isClosed();
	if (shouldClose_) {
		gripper_->close();
	} else {
		gripper_->open();
	}
}

void GripCommand::undo()
{
	if (previousClosed_) {
		gripper_->close();
	} else {
		gripper_->open();
	}
}

std::string GripCommand::name() const
{
	return shouldClose_ ? "파지" : "놓기";
}
