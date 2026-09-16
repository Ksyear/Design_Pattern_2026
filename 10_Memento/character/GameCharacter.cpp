#include "character/GameCharacter.h"

#include <iostream>
#include <utility>

GameCharacter::Memento::Memento(int level, int hp, std::string weapon, std::string label)
	: level_(level), hp_(hp), weapon_(std::move(weapon)), label_(std::move(label)) {}

GameCharacter::GameCharacter(std::string name) : name_(std::move(name)) {}

void GameCharacter::levelUp(const std::string& newWeapon) {
	++level_;
	hp_ = 100 + level_ * 20;
	weapon_ = newWeapon;
}

void GameCharacter::takeDamage(int dmg) {
	hp_ = hp_ > dmg ? hp_ - dmg : 0;
}

bool GameCharacter::isDead() const {
	return hp_ == 0;
}

void GameCharacter::show() const {
	std::cout << "  " << name_ << " | 레벨 " << level_ << " | HP " << hp_ << " | 무기 "
	          << weapon_ << (isDead() ? "  <사망>" : "") << '\n';
}

std::unique_ptr<GameCharacter::Memento> GameCharacter::save(const std::string& label) const {
	return std::unique_ptr<Memento>(new Memento(level_, hp_, weapon_, label));
}

void GameCharacter::restore(const Memento& m) {
	level_ = m.level_;
	hp_ = m.hp_;
	weapon_ = m.weapon_;
}
