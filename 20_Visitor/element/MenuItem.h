#ifndef ELEMENT_MENU_ITEM_H
#define ELEMENT_MENU_ITEM_H

#include <string>
#include <vector>

#include "element/Ingredient.h"
#include "element/MenuComponent.h"
#include "visitor/Visitor.h"

class MenuItem : public MenuComponent {
public:
	MenuItem(std::string name, std::vector<Ingredient> ingredients);

	const std::string& name() const;
	const std::vector<Ingredient>& ingredients() const;

	// 트래버서 역할 - 자식까지 데리고 다닌다 (컴포지트 + 비지터의 전형적인 결합)
	void accept(Visitor& v) const override;

private:
	std::string name_;
	std::vector<Ingredient> ingredients_;
};

#endif
