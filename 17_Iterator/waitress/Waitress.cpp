#include "waitress/Waitress.h"

#include <iostream>
#include <utility>

#include "menu/MenuItem.h"

Waitress::Waitress(std::vector<const Menu*> menus) : menus_(std::move(menus)) {}

void Waitress::printMenu() const {
	for (const Menu* m : menus_) {
		std::cout << "== " << m->title() << " ==\n";
		printIterator(*m->createIterator());
	}
}

void Waitress::printVegetarianMenu() const {
	std::cout << "== 채식 메뉴 ==\n";
	for (const Menu* m : menus_) {
		auto it = m->createIterator();
		while (it->hasNext()) {
			const MenuItem& item = it->next();
			if (item.vegetarian) std::cout << "  " << item.name << '\n';
		}
	}
}

void Waitress::printIterator(Iterator& it) {
	while (it.hasNext()) {
		const MenuItem& item = it.next();
		std::cout << "  " << item.name << " ($" << item.price << ") - " << item.description
		          << '\n';
	}
}
