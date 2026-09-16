#ifndef COMMAND_MACRO_COMMAND_H
#define COMMAND_MACRO_COMMAND_H

#include <vector>

#include "command/Command.h"

// MacroCommand : 커맨드를 담는 커맨드 (컴포지트 성격).
// Command 인터페이스를 구현하므로 인보커 입장에서는 낱개 커맨드와 구별되지 않는다.
class MacroCommand : public Command {
public:
	explicit MacroCommand(std::vector<Command*> commands);
	void execute() override;
	void undo() override;

private:
	std::vector<Command*> commands_;
};

#endif
