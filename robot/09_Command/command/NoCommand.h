#ifndef COMMAND_NOCOMMAND_H
#define COMMAND_NOCOMMAND_H

#include "command/Command.h"

// 널 객체 - 아직 아무것도 할당되지 않은 버튼.
// 덕분에 콘솔 쪽에 "이 슬롯이 비었는지" 검사하는 if 가 필요 없다.
class NoCommand : public Command {
public:
	void execute() override;
	void undo() override;
	std::string name() const override;
};

#endif
