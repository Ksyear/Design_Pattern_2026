#include "monster/Slime.h"

#include <iostream>

Slime::Slime() : Monster("슬라임", 30, {"몸통 박치기"}) {}

std::unique_ptr<Monster> Slime::clone() const {
	// 복사 생성자를 그대로 쓰되, 반환 타입을 기반 포인터로 맞춘다
	return std::make_unique<Slime>(*this);
}

void Slime::describe() const {
	std::cout << "[슬라임] " << name() << " HP=" << hp() << " 기술=";
	for (const auto& s : skills()) std::cout << s << ' ';
	std::cout << '\n';
}
