#include "forest/Forest.h"

#include <cstddef>
#include <iostream>

void Forest::plantTree(int x, int y, int age, const std::string& name, const std::string& color,
                       const std::string& texture) {
	const TreeType& type = factory_.getTreeType(name, color, texture);
	trees_.emplace_back(x, y, age, type);
}

void Forest::draw() const {
	for (const auto& t : trees_) t.draw();
}

void Forest::report() const {
	std::cout << "\n나무 개수: " << trees_.size() << " 그루\n";
	std::cout << "실제 TreeType 인스턴스: " << factory_.poolSize() << " 개\n";
	const std::size_t naive = trees_.size() * (sizeof(Tree) + 3 * 32);   // 문자열 3개 대략치
	const std::size_t actual = trees_.size() * sizeof(Tree) + factory_.poolSize() * 3 * 32;
	std::cout << "대략 메모리: 플라이웨이트 미적용 " << naive << " B -> 적용 " << actual << " B\n";
}
