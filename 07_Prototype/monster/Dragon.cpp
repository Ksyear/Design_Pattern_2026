#include "monster/Dragon.h"

#include <iostream>

Dragon::Dragon() : Monster("드래곤", 500, {"화염 브레스"}) {}

std::unique_ptr<Monster> Dragon::clone() const {
	// 복사 생성자를 그대로 쓰되, 반환 타입을 기반 포인터로 맞춘다
	return std::make_unique<Dragon>(*this);
}

void Dragon::describe() const {
	std::cout << "[용] " << name() << " HP=" << hp() << " 기술=";
	for (const auto& s : skills()) std::cout << s << ' ';
	std::cout << '\n';
}
