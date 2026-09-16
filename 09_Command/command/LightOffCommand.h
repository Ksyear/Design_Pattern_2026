#ifndef COMMAND_LIGHT_OFF_COMMAND_H
#define COMMAND_LIGHT_OFF_COMMAND_H

#include "command/Command.h"
#include "device/Light.h"

// ConcreteCommand : 리시버 + 행동을 한 객체에 묶는다
class LightOffCommand : public Command {
public:
	explicit LightOffCommand(Light& light);
	void execute() override;
	void undo() override;

private:
	Light& light_;
};

#endif
