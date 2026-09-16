#ifndef ELEMENT_MENU_H
#define ELEMENT_MENU_H

#include <memory>
#include <string>
#include <vector>

#include "element/MenuComponent.h"
#include "visitor/Visitor.h"

class Menu : public MenuComponent {
public:
	explicit Menu(std::string name);

	void add(std::shared_ptr<MenuComponent> c);
	const std::string& name() const;

	void accept(Visitor& v) const override;

private:
	std::string name_;
	std::vector<std::shared_ptr<MenuComponent>> children_;
};

#endif
