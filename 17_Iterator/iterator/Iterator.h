#ifndef ITERATOR_ITERATOR_H
#define ITERATOR_ITERATOR_H

#include "menu/MenuItem.h"

// (1) GoF 스타일 명시적 Iterator 인터페이스 (책의 구현)
//
// 핵심: 집합체의 내부 구현(배열이냐 vector냐 map이냐)을 노출하지 않고
//       항목을 하나씩 훑는 방법을 제공한다.
//       -> 종업원 코드(printMenu)는 컬렉션 종류를 몰라도 된다.
class Iterator {
public:
	virtual ~Iterator() = default;
	virtual bool hasNext() const = 0;
	virtual const MenuItem& next() = 0;
};

#endif
