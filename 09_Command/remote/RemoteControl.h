#ifndef REMOTE_REMOTE_CONTROL_H
#define REMOTE_REMOTE_CONTROL_H

#include "command/Command.h"
#include "command/NoCommand.h"

// Invoker : 커맨드만 알고 리시버는 전혀 모른다.
// 이 헤더에 Light 도 CeilingFan 도 등장하지 않는다는 점이 패턴의 성과다.
class RemoteControl {
public:
	static constexpr int kSlots = 7;

	RemoteControl();

	void setCommand(int slot, Command* on, Command* off);

	void onButtonWasPushed(int slot);
	void offButtonWasPushed(int slot);
	void undoButtonWasPushed();

private:
	NoCommand noCommand_;
	Command* onCommands_[kSlots];
	Command* offCommands_[kSlots];
	Command* undoCommand_;
};

#endif
