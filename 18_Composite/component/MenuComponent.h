#ifndef COMPONENT_MENU_COMPONENT_H
#define COMPONENT_MENU_COMPONENT_H

#include <memory>
#include <string>

// Component
//
// 핵심: 부분-전체 계층구조(part-whole hierarchy)를 트리로 만들고,
//       클라이언트가 '잎(MenuItem)'과 '노드(Menu)'를 똑같이 다루게 한다.
//
// 투명성 vs 안전성 (책 9장이 명시적으로 다루는 트레이드오프)
//   - 투명성(transparency): Component 에 add/remove 를 다 두면 클라이언트가 구분할 필요가 없다
//                           대신 MenuItem::add() 는 의미가 없어 예외를 던지게 된다
//   - 안전성(safety)      : add/remove 를 Composite 에만 두면 타입 안전하지만
//                           클라이언트가 dynamic_cast 로 구분해야 한다
//   GoF와 이 책은 '투명성'을 택했다. 여기서도 그 선택을 따른다.
class MenuComponent {
public:
	virtual ~MenuComponent() = default;

	// 복합 객체용 연산 - 잎에서는 의미가 없다
	virtual void add(std::shared_ptr<MenuComponent>);
	virtual void remove(const std::shared_ptr<MenuComponent>&);

	// 잎용 연산 - 복합 객체에서는 의미가 없다
	virtual const std::string& getName() const;
	virtual const std::string& getDescription() const;
	virtual double getPrice() const;
	virtual bool isVegetarian() const;

	// 둘 다 구현하는 연산 - 클라이언트는 이것만 부른다
	virtual void print(int depth = 0) const = 0;

protected:
	static std::string indent(int depth);
};

#endif
