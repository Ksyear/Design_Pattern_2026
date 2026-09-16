#ifndef ITERATOR_PANCAKE_HOUSE_MENU_ITERATOR_H
#define ITERATOR_PANCAKE_HOUSE_MENU_ITERATOR_H

#include <cstddef>

#include "iterator/Iterator.h"
#include "menu/MenuItem.h"
#include "menu/PancakeHouseMenu.h"

class PancakeHouseMenuIterator : public Iterator {
public:
	explicit PancakeHouseMenuIterator(const PancakeHouseMenu& menu);
	bool hasNext() const override;
	const MenuItem& next() override;

private:
	const PancakeHouseMenu& menu_;
	std::size_t pos_ = 0;
};

#endif
