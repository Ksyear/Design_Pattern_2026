#include "monster/Monster.h"

#include <utility>

Monster::Monster(std::string name, int hp, std::vector<std::string> skills)
	: name_(std::move(name)), hp_(hp), skills_(std::move(skills)) {}

void Monster::setName(std::string n) {
	name_ = std::move(n);
}

void Monster::addSkill(std::string s) {
	skills_.push_back(std::move(s));
}

const std::string& Monster::name() const {
	return name_;
}

int Monster::hp() const {
	return hp_;
}

const std::vector<std::string>& Monster::skills() const {
	return skills_;
}
