#ifndef MENU_PANCAKE_HOUSE_MENU_H
#define MENU_PANCAKE_HOUSE_MENU_H

#include <memory>
#include <string>
#include <vector>

#include "iterator/Iterator.h"
#include "menu/Menu.h"
#include "menu/MenuItem.h"

// 내부가 vector 인 메뉴 - 구현이 전혀 다른데도 같은 Iterator 를 돌려준다
class PancakeHouseMenu : public Menu {
public:
	PancakeHouseMenu();

	std::unique_ptr<Iterator> createIterator() const override;
	const std::string& title() const override;

private:
	friend class PancakeHouseMenuIterator;
	std::vector<MenuItem> items_;
	std::string title_ = "팬케이크 하우스 (아침 메뉴)";
};

#endif
