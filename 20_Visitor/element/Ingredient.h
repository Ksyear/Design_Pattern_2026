#ifndef ELEMENT_INGREDIENT_H
#define ELEMENT_INGREDIENT_H

#include <string>

#include "element/MenuComponent.h"
#include "visitor/Visitor.h"

// 잎 element.
// 비지터는 상태를 읽어야 하므로 getState()류를 공개해야 한다
// -> "비지터를 쓰면 복합 클래스의 캡슐화가 깨진다"는 단점이 여기서 나온다.
class Ingredient : public MenuComponent {
public:
	Ingredient(std::string name, int calories, int protein, int carbs);

	const std::string& name() const;
	int calories() const;
	int protein() const;
	int carbs() const;

	void accept(Visitor& v) const override;

private:
	std::string name_;
	int calories_;
	int protein_;
	int carbs_;
};

#endif
