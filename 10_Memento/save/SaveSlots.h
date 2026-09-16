#ifndef SAVE_SAVE_SLOTS_H
#define SAVE_SAVE_SLOTS_H

#include <memory>
#include <vector>

#include "character/GameCharacter.h"

// Caretaker
// 언제 저장하고 언제 되돌릴지만 결정한다. 메멘토 내부는 절대 건드리지 않는다.
// (m->level_ 에 접근하면 컴파일 에러 -> 캡슐화가 문법으로 강제된다)
class SaveSlots {
public:
	void push(std::unique_ptr<GameCharacter::Memento> m);
	const GameCharacter::Memento* last() const;
	void list() const;

private:
	std::vector<std::unique_ptr<GameCharacter::Memento>> slots_;
};

#endif
