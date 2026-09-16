#ifndef ELEMENT_MENU_COMPONENT_H
#define ELEMENT_MENU_COMPONENT_H

#include "visitor/Visitor.h"

// Element
//
// 이중 디스패치(double dispatch)
//   element->accept(visitor) -> visitor.visit(*this)
//   1차: 어떤 element 인가 (가상 호출)
//   2차: 어떤 visitor 인가 (오버로드 해석)
//   C++에는 다중 디스패치가 없으므로 이 2단계 우회가 필요하다.
class MenuComponent {
public:
	virtual ~MenuComponent() = default;
	virtual void accept(Visitor& v) const = 0;
};

#endif
