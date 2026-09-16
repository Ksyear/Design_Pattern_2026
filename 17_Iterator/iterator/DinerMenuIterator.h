#ifndef ITERATOR_DINER_MENU_ITERATOR_H
#define ITERATOR_DINER_MENU_ITERATOR_H

#include <cstddef>

#include "iterator/Iterator.h"
#include "menu/DinerMenu.h"
#include "menu/MenuItem.h"

// 배열을 훑는 반복자. 위치(pos_)를 자기가 들고 있으므로
// 같은 메뉴에 반복자를 여러 개 만들어 동시에 돌릴 수 있다.
class DinerMenuIterator : public Iterator {
public:
	explicit DinerMenuIterator(const DinerMenu& menu);
	bool hasNext() const override;
	const MenuItem& next() override;

private:
	const DinerMenu& menu_;
	std::size_t pos_ = 0;
};

#endif
