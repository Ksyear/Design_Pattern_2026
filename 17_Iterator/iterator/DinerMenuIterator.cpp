#include "iterator/DinerMenuIterator.h"

DinerMenuIterator::DinerMenuIterator(const DinerMenu& menu) : menu_(menu) {}

bool DinerMenuIterator::hasNext() const {
	return pos_ < menu_.count_;
}

const MenuItem& DinerMenuIterator::next() {
	return menu_.items_[pos_++];
}
