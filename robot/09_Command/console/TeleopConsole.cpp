#include "console/TeleopConsole.h"

#include <iostream>
#include <utility>

#include "command/NoCommand.h"

TeleopConsole::TeleopConsole()
{
	// 널 객체로 채워 두면 press() 안에 nullptr 검사가 필요 없다
	for (std::unique_ptr<Command>& slot : slots_) {
		slot = std::make_unique<NoCommand>();
	}
}

void TeleopConsole::assign(std::size_t slot, std::unique_ptr<Command> command)
{
	if (slot >= kSlotCount || !command) {
		return;
	}
	std::cout << "  슬롯 " << slot << " <- " << command->name() << '\n';
	slots_[slot] = std::move(command);
}

void TeleopConsole::press(std::size_t slot)
{
	if (slot >= kSlotCount) {
		return;
	}
	std::cout << "    버튼 " << slot << " (" << slots_[slot]->name() << ")\n";
	slots_[slot]->execute();
	history_.push_back(slots_[slot].get());
}

void TeleopConsole::undoLast()
{
	if (history_.empty()) {
		std::cout << "    되돌릴 기록이 없습니다\n";
		return;
	}
	Command* last = history_.back();
	history_.pop_back();
	std::cout << "    되돌리기 (" << last->name() << ")\n";
	last->undo();
}

void TeleopConsole::printSlots() const
{
	std::cout << "  [콘솔]";
	for (const std::unique_ptr<Command>& slot : slots_) {
		std::cout << " | " << slot->name();
	}
	std::cout << " |\n";
}
