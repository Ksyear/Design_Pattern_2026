#ifndef COMMAND_MACROCOMMAND_H
#define COMMAND_MACROCOMMAND_H

#include <memory>
#include <vector>

#include "command/Command.h"

// 매크로 - 명령 여러 개를 하나의 명령처럼 다룬다.
//
// MacroCommand 자체가 Command 이기 때문에 콘솔 쪽은 차이를 모른다.
// (18_Composite 와 같은 발상이다 : 하나와 여럿을 같은 형식으로 다룬다)
//
// 로봇에서의 자리 : 비헤이비어 트리의 Sequence 노드,
// MoveIt 의 여러 구간을 묶은 궤적, "집품 시퀀스" 같은 작업 단위.
class MacroCommand : public Command {
public:
	MacroCommand(std::string name, std::vector<std::unique_ptr<Command>> steps);

	void execute() override;
	void undo() override;   // 역순으로 되돌린다 - 순서가 중요하다
	std::string name() const override;

private:
	std::string name_;
	std::vector<std::unique_ptr<Command>> steps_;
};

#endif
