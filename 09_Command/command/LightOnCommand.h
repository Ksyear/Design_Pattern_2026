#ifndef COMMAND_LIGHT_ON_COMMAND_H
#define COMMAND_LIGHT_ON_COMMAND_H

#include "command/Command.h"
#include "device/Light.h"

// ConcreteCommand : 리시버 + 행동을 한 객체에 묶는다
class LightOnCommand : public Command {
public:
	explicit LightOnCommand(Light& light);
	void execute() override;
	void undo() override;

private:
	Light& light_;
};

#endif
