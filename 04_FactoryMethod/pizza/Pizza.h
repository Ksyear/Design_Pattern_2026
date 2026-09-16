#ifndef PIZZA_PIZZA_H
#define PIZZA_PIZZA_H

#include <string>
#include <vector>

// Product : 만들어지는 물건. 지역 스타일은 이 클래스를 상속해 차이만 덮어쓴다.
//
// 이름과 토핑은 생성자로 받는다. 서브클래스가 몸통에서 대입하던 방식을 걷어내
// "이름 없는 피자"가 잠시라도 존재하지 않게 했다.
class Pizza {
public:
	virtual ~Pizza() = default;

	virtual void prepare() const;
	virtual void bake() const;
	virtual void cut() const;
	virtual void box() const;

	const std::string& getName() const;

protected:
	Pizza(std::string name, std::vector<std::string> toppings);

private:
	std::string name_;
	std::vector<std::string> toppings_;
};

#endif
