#ifndef COMMAND_MOVECOMMAND_H
#define COMMAND_MOVECOMMAND_H

#include "command/Command.h"
#include "device/MobileBase.h"

// 앞으로 얼마 - 값까지 함께 담긴다.
// 받는 쪽은 원시 포인터로 들고 있다 : 명령이 장치를 소유하지는 않는다.
class MoveCommand : public Command {
public:
	MoveCommand(MobileBase* base, double meters);

	void execute() override;
	void undo() override;
	std::string name() const override;

private:
	MobileBase* base_;  // 비소유 참조
	double meters_;
};

#endif
