#ifndef COMMAND_CEILING_FAN_COMMAND_H
#define COMMAND_CEILING_FAN_COMMAND_H

#include "command/Command.h"
#include "device/CeilingFan.h"

// 상태를 되돌려야 하는 작업 취소 - 실행 직전 상태를 기억해 둔다
class CeilingFanCommand : public Command {
public:
	CeilingFanCommand(CeilingFan& fan, CeilingFan::Speed target);
	void execute() override;
	void undo() override;

private:
	CeilingFan& fan_;
	CeilingFan::Speed target_;
	CeilingFan::Speed prevSpeed_ = CeilingFan::Off;
};

#endif
