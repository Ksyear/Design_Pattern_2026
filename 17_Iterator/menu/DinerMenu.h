#ifndef MENU_DINER_MENU_H
#define MENU_DINER_MENU_H

#include <array>
#include <cstddef>
#include <memory>
#include <string>

#include "iterator/Iterator.h"
#include "menu/Menu.h"
#include "menu/MenuItem.h"

// 내부가 고정 크기 배열인 메뉴
class DinerMenu : public Menu {
public:
	static constexpr std::size_t kMax = 6;

	DinerMenu();

	void addItem(MenuItem item);

	std::unique_ptr<Iterator> createIterator() const override;
	const std::string& title() const override;

private:
	friend class DinerMenuIterator;   // 반복자에게만 내부를 연다
	std::array<MenuItem, kMax> items_{};
	std::size_t count_ = 0;
	std::string title_ = "객체마을 식당 (점심 메뉴)";
};

#endif
