#ifndef MENU_MENU_ITEM_H
#define MENU_MENU_ITEM_H

#include <string>

// 컬렉션이 담는 항목
struct MenuItem {
	std::string name;
	std::string description;
	bool vegetarian = false;
	double price = 0.0;
};

#endif
