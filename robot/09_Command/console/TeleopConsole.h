#ifndef CONSOLE_TELEOPCONSOLE_H
#define CONSOLE_TELEOPCONSOLE_H

#include <array>
#include <memory>
#include <vector>

#include "command/Command.h"

// Invoker - 버튼을 누르면 슬롯에 꽂힌 명령을 실행할 뿐,
// 그것이 바퀴를 돌리는지 그리퍼를 닫는지 전혀 모른다.
//
// 이 무지함이 핵심이다. 장치가 몇 개로 늘어나도 이 클래스는 그대로다.
// 조이스틱 노드, 웹 관제 화면, 자동 스크립트가 전부 이 자리에 온다.
class TeleopConsole {
public:
	static constexpr std::size_t kSlotCount = 4;

	TeleopConsole();

	void assign(std::size_t slot, std::unique_ptr<Command> command);
	void press(std::size_t slot);
	void undoLast();
	void printSlots() const;

private:
	std::array<std::unique_ptr<Command>, kSlotCount> slots_;
	std::vector<Command*> history_;  // 비소유 - 실제 명령은 슬롯이 들고 있다
};

#endif
