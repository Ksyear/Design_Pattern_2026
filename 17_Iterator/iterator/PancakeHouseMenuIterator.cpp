#include "iterator/PancakeHouseMenuIterator.h"

PancakeHouseMenuIterator::PancakeHouseMenuIterator(const PancakeHouseMenu& menu) : menu_(menu) {}

bool PancakeHouseMenuIterator::hasNext() const {
	return pos_ < menu_.items_.size();
}

const MenuItem& PancakeHouseMenuIterator::next() {
	return menu_.items_[pos_++];
}
