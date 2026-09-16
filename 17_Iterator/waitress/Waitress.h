#ifndef WAITRESS_WAITRESS_H
#define WAITRESS_WAITRESS_H

#include <vector>

#include "iterator/Iterator.h"
#include "menu/Menu.h"

// Client : 종업원. 컬렉션 종류를 전혀 모른다.
// 이 헤더에 DinerMenu 도 PancakeHouseMenu 도 등장하지 않는 것이 성과다.
class Waitress {
public:
	explicit Waitress(std::vector<const Menu*> menus);

	void printMenu() const;
	void printVegetarianMenu() const;

private:
	static void printIterator(Iterator& it);

	std::vector<const Menu*> menus_;
};

#endif
