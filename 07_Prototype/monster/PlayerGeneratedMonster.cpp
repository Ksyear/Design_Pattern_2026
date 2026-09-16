#include "monster/PlayerGeneratedMonster.h"

#include <iostream>
#include <utility>

PlayerGeneratedMonster::PlayerGeneratedMonster(std::string name, int hp,
                                               std::vector<std::string> skills)
	: Monster(std::move(name), hp, std::move(skills)) {}

std::unique_ptr<Monster> PlayerGeneratedMonster::clone() const {
	return std::make_unique<PlayerGeneratedMonster>(*this);
}

void PlayerGeneratedMonster::describe() const {
	std::cout << "[유저 제작] " << name() << " HP=" << hp() << " 기술=";
	for (const auto& s : skills()) std::cout << s << ' ';
	std::cout << '\n';
}
