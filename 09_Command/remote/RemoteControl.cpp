#include "remote/RemoteControl.h"

#include <iostream>

RemoteControl::RemoteControl() {
	for (int i = 0; i < kSlots; ++i) {
		onCommands_[i] = &noCommand_;
		offCommands_[i] = &noCommand_;
	}
	undoCommand_ = &noCommand_;
}

void RemoteControl::setCommand(int slot, Command* on, Command* off) {
	onCommands_[slot] = on;
	offCommands_[slot] = off;
}

void RemoteControl::onButtonWasPushed(int slot) {
	onCommands_[slot]->execute();
	undoCommand_ = onCommands_[slot];
}

void RemoteControl::offButtonWasPushed(int slot) {
	offCommands_[slot]->execute();
	undoCommand_ = offCommands_[slot];
}

void RemoteControl::undoButtonWasPushed() {
	std::cout << "[취소] ";
	undoCommand_->undo();
}
