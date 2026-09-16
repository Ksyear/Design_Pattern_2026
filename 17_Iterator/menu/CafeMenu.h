#ifndef MENU_CAFE_MENU_H
#define MENU_CAFE_MENU_H

#include <vector>

#include "menu/MenuItem.h"

// (2) STL 규약을 따르는 반복자
// begin()/end() 와 최소한의 연산자만 갖추면 범위 기반 for 가 공짜로 따라온다.
// Menu 인터페이스를 상속하지 않는다는 점에 주목 - 규약이 인터페이스를 대신한다.
class CafeMenu {
public:
	CafeMenu();

	using const_iterator = std::vector<MenuItem>::const_iterator;
	const_iterator begin() const;
	const_iterator end() const;

private:
	std::vector<MenuItem> items_;
};

#endif
