#include "command/LightOnCommand.h"

LightOnCommand::LightOnCommand(Light& light) : light_(light) {}

void LightOnCommand::execute() {
	light_.on();
}

void LightOnCommand::undo() {
	light_.off();
}
