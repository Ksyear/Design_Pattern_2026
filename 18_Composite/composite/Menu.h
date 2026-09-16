#ifndef COMPOSITE_MENU_H
#define COMPOSITE_MENU_H

#include <memory>
#include <string>
#include <vector>

#include "component/MenuComponent.h"

// Composite : 자식을 담는 노드. 자식이 잎인지 노드인지 묻지 않는다.
class Menu : public MenuComponent {
public:
	Menu(std::string name, std::string description);

	void add(std::shared_ptr<MenuComponent> c) override;
	void remove(const std::shared_ptr<MenuComponent>& c) override;

	const std::string& getName() const override;
	const std::string& getDescription() const override;

	// 재귀 - 컴포지트 패턴의 핵심
	void print(int depth = 0) const override;

	// 트리 전체를 대상으로 한 연산도 재귀로 간단해진다
	double totalPrice() const;

private:
	std::string name_;
	std::string description_;
	std::vector<std::shared_ptr<MenuComponent>> children_;
};

#endif
