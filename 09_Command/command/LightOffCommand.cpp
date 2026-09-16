#include "command/LightOffCommand.h"

LightOffCommand::LightOffCommand(Light& light) : light_(light) {}

void LightOffCommand::execute() {
	light_.off();
}

void LightOffCommand::undo() {
	light_.on();
}
