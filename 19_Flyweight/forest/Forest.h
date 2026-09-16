#ifndef FOREST_FOREST_H
#define FOREST_FOREST_H

#include <string>
#include <vector>

#include "factory/TreeFactory.h"
#include "forest/Tree.h"

// 클라이언트 쪽 컬렉션. 나무를 심을 때마다 공장을 거치므로
// 같은 종류는 저절로 같은 TreeType 을 가리키게 된다.
class Forest {
public:
	void plantTree(int x, int y, int age, const std::string& name, const std::string& color,
	               const std::string& texture);

	void draw() const;
	void report() const;

private:
	TreeFactory factory_;
	std::vector<Tree> trees_;
};

#endif
