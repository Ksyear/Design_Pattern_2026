#ifndef FLYWEIGHT_TREE_TYPE_H
#define FLYWEIGHT_TREE_TYPE_H

#include <string>

// Flyweight : 내부 상태만 들고, 외부 상태는 인자로 받는다.
//
// 핵심: 객체 상태를 두 가지로 쪼갠다.
//   - 내부 상태(intrinsic) : 여러 객체가 공유할 수 있는 불변 데이터 (종류, 스프라이트, 색)
//   - 외부 상태(extrinsic) : 객체마다 다른 데이터 (x, y, 나이) -> 메소드 인자나 문맥 객체로 뺀다
//
// 주의: 내부 상태는 반드시 불변이어야 한다. 하나를 바꾸면 공유하는 전부가 바뀐다.
//       -> "특정 인스턴스만 다르게 행동하게 할 수 없다"는 단점이 여기서 나온다.
class TreeType {
public:
	TreeType(std::string name, std::string color, std::string texture);

	// x, y, age 가 매개변수로 들어온다 -> 이 객체는 위치를 '모른다'
	void draw(int x, int y, int age) const;

	const std::string& name() const;

private:
	// 전부 const - 공유되므로 절대 바뀌면 안 된다
	const std::string name_;
	const std::string color_;
	const std::string texture_;
};

#endif
