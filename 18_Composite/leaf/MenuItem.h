#ifndef LEAF_MENU_ITEM_H
#define LEAF_MENU_ITEM_H

#include <string>

#include "component/MenuComponent.h"

// Leaf : 자식이 없는 끝단. add/remove 는 물려받은 '예외를 던지는' 구현을 그대로 쓴다.
class MenuItem : public MenuComponent {
public:
	MenuItem(std::string name, std::string description, bool vegetarian, double price);

	const std::string& getName() const override;
	const std::string& getDescription() const override;
	double getPrice() const override;
	bool isVegetarian() const override;

	void print(int depth = 0) const override;

private:
	std::string name_;
	std::string description_;
	bool vegetarian_;
	double price_;
};

#endif
