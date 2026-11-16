#ifndef COMMAND_TURNCOMMAND_H
#define COMMAND_TURNCOMMAND_H

#include "command/Command.h"
#include "device/MobileBase.h"

class TurnCommand : public Command {
public:
	TurnCommand(MobileBase* base, double degrees);

	void execute() override;
	void undo() override;
	std::string name() const override;

private:
	MobileBase* base_;
	double degrees_;
};

#endif
