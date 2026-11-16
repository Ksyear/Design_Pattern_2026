#ifndef COMMAND_GRIPCOMMAND_H
#define COMMAND_GRIPCOMMAND_H

#include "command/Command.h"
#include "device/Gripper.h"

// 파지 명령. undo 하려면 "원래 어땠는지" 를 기억해야 한다.
// 이 기억이 바로 10_Memento 로 이어지는 지점이다.
class GripCommand : public Command {
public:
	GripCommand(Gripper* gripper, bool shouldClose);

	void execute() override;
	void undo() override;
	std::string name() const override;

private:
	Gripper* gripper_;
	bool shouldClose_;
	bool previousClosed_ = false;  // 실행 직전 상태를 적어 둔다
};

#endif
