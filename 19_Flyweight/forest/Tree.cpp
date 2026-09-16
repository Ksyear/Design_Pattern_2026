#include "forest/Tree.h"

Tree::Tree(int x, int y, int age, const TreeType& type)
	: x_(x), y_(y), age_(age), type_(&type) {}

void Tree::draw() const {
	type_->draw(x_, y_, age_);
}
