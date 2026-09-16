#include "menu/PancakeHouseMenu.h"

#include "iterator/PancakeHouseMenuIterator.h"

PancakeHouseMenu::PancakeHouseMenu() {
	items_ = {
		{"K&B 팬케이크 세트", "스크램블 에그와 토스트가 곁들여진 팬케이크", true, 2.99},
		{"레귤러 팬케이크 세트", "달걀 프라이와 소시지가 곁들여진 팬케이크", false, 2.99},
		{"블루베리 팬케이크", "신선한 블루베리로 만든 팬케이크", true, 3.49},
	};
}

std::unique_ptr<Iterator> PancakeHouseMenu::createIterator() const {
	return std::make_unique<PancakeHouseMenuIterator>(*this);
}

const std::string& PancakeHouseMenu::title() const {
	return title_;
}
