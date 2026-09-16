#ifndef COMMAND_NO_COMMAND_H
#define COMMAND_NO_COMMAND_H

#include "command/Command.h"

// 널 객체(Null Object) - 빈 슬롯에서 if(cmd != nullptr) 검사를 없애 준다
class NoCommand : public Command {
public:
	void execute() override;
	void undo() override;
};

#endif
