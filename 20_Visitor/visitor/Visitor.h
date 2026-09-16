#ifndef VISITOR_VISITOR_H
#define VISITOR_VISITOR_H

class MenuItem;
class Menu;
class Ingredient;

// Visitor 인터페이스 : element 종류마다 메소드 하나
//
// 핵심: 객체 구조는 그대로 두고, 새 '연산'만 바깥에서 추가한다.
//       MenuItem/Ingredient 에 getCalories(), getProtein()... 을 계속 붙이는 대신
//       Visitor 클래스 하나를 새로 만들면 끝난다.
//
// 대가: element 종류를 하나 추가하면 '모든' Visitor 를 고쳐야 한다.
//       -> element 가 자주 늘어나는 구조에는 쓰면 안 된다.
//       이 헤더가 element 를 전부 전방 선언한다는 점이 그 결합을 보여 준다.
class Visitor {
public:
	virtual ~Visitor() = default;
	virtual void visit(const MenuItem& item) = 0;
	virtual void visit(const Menu& menu) = 0;
	virtual void visit(const Ingredient& ing) = 0;
};

#endif
