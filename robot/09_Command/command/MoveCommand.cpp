#include "command/MoveCommand.h"

#include <stdexcept>

MoveCommand::MoveCommand(MobileBase* base, double meters)
	: base_(base), meters_(meters)
{
	if (base_ == nullptr) {
		throw std::invalid_argument("MoveCommand 에 장치가 필요합니다");
	}
}

void MoveCommand::execute()
{
	base_->driveForward(meters_);
}

void MoveCommand::undo()
{
	// 로봇에서 undo 는 "없던 일로" 가 아니라 "반대로 움직이기" 다.
	// 완벽하게 제자리로 돌아오지 않는다는 점(슬립, 오차)도 현실의 일부다.
	base_->driveForward(-meters_);
}

std::string MoveCommand::name() const
{
	return "전진";
}
