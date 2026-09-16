#include "save/SaveSlots.h"

#include <iostream>
#include <utility>

void SaveSlots::push(std::unique_ptr<GameCharacter::Memento> m) {
	std::cout << "[세이브] " << m->label() << '\n';
	slots_.push_back(std::move(m));
}

const GameCharacter::Memento* SaveSlots::last() const {
	return slots_.empty() ? nullptr : slots_.back().get();
}

void SaveSlots::list() const {
	std::cout << "  보관 중인 세이브: ";
	for (const auto& m : slots_) std::cout << '[' << m->label() << "] ";
	std::cout << '\n';
}
