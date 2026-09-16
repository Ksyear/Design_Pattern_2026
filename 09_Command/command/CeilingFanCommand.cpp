#include "command/CeilingFanCommand.h"

CeilingFanCommand::CeilingFanCommand(CeilingFan& fan, CeilingFan::Speed target)
	: fan_(fan), target_(target) {}

void CeilingFanCommand::execute() {
	prevSpeed_ = fan_.getSpeed();
	fan_.setSpeed(target_);
}

void CeilingFanCommand::undo() {
	fan_.setSpeed(prevSpeed_);
}
