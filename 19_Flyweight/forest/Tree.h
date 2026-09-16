#ifndef FOREST_TREE_H
#define FOREST_TREE_H

#include "flyweight/TreeType.h"

// Context : 외부 상태 + 플라이웨이트 참조.
// 가볍다. 포인터 하나 + int 세 개뿐.
class Tree {
public:
	Tree(int x, int y, int age, const TreeType& type);
	void draw() const;

private:
	int x_;
	int y_;
	int age_;
	const TreeType* type_;
};

#endif
