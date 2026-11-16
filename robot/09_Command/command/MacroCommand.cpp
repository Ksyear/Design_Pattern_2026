#include "command/MacroCommand.h"

#include <iostream>
#include <utility>

MacroCommand::MacroCommand(std::string name, std::vector<std::unique_ptr<Command>> steps)
	: name_(std::move(name)), steps_(std::move(steps))
{
}

void MacroCommand::execute()
{
	std::cout << "      [매크로 " << name_ << " 시작]\n";
	for (const std::unique_ptr<Command>& step : steps_) {
		step->execute();
	}
}

void MacroCommand::undo()
{
	std::cout << "      [매크로 " << name_ << " 되돌리기 - 역순]\n";
	// 앞에서부터 되돌리면 안 된다. 집은 물건을 놓기 전에 후진하면 물건이 끌려온다.
	for (auto it = steps_.rbegin(); it != steps_.rend(); ++it) {
		(*it)->undo();
	}
}

std::string MacroCommand::name() const
{
	return name_;
}
