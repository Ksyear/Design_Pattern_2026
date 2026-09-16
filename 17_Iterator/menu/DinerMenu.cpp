#include "menu/DinerMenu.h"

#include <utility>

#include "iterator/DinerMenuIterator.h"

DinerMenu::DinerMenu() {
	addItem({"채식주의자용 BLT", "통밀 위에 콩고기 베이컨, 상추, 토마토", true, 2.99});
	addItem({"BLT", "통밀 위에 베이컨, 상추, 토마토", false, 2.99});
	addItem({"오늘의 스프", "감자 샐러드를 곁들인 오늘의 스프", false, 3.29});
	addItem({"핫도그", "사워크라우트, 양념, 양파, 치즈가 들어간 핫도그", false, 3.05});
}

void DinerMenu::addItem(MenuItem item) {
	if (count_ < kMax) items_[count_++] = std::move(item);
}

std::unique_ptr<Iterator> DinerMenu::createIterator() const {
	return std::make_unique<DinerMenuIterator>(*this);
}

const std::string& DinerMenu::title() const {
	return title_;
}
