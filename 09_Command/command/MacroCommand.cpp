#include "command/MacroCommand.h"

#include <utility>

MacroCommand::MacroCommand(std::vector<Command*> commands) : commands_(std::move(commands)) {}

void MacroCommand::execute() {
	for (auto* c : commands_) c->execute();
}

void MacroCommand::undo() {
	// 취소는 역순이어야 부작용이 없다
	for (auto it = commands_.rbegin(); it != commands_.rend(); ++it) (*it)->undo();
}
