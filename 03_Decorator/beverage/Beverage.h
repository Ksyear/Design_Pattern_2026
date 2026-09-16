#ifndef BEVERAGE_BEVERAGE_H
#define BEVERAGE_BEVERAGE_H

#include <string>

// Component : 음료와 첨가물이 공유하는 단 하나의 타입.
// 데코레이터도 이 타입을 구현하기 때문에 감싼 결과물을 다시 감쌀 수 있다.
//
// 설명은 생성자로 받는다(생성자 주입). 서브클래스가 몸통에서 description_ 에
// 대입하지 못하도록 필드를 private 으로 닫았다 -> 01_Strategy/duck 과 같은 규약.
class Beverage {
public:
	enum class Size { Tall, Grande, Venti };

	virtual ~Beverage() = default;
	virtual std::string getDescription() const;
	virtual double cost() const = 0;

	virtual void setSize(Size s);
	virtual Size getSize() const;

protected:
	// 서브클래스 전용 생성자. 데코레이터는 설명을 직접 만들어 쓰므로 기본값을 둔다.
	explicit Beverage(std::string description = "제목 없음");

private:
	std::string description_;
	Size size_ = Size::Tall;
};

#endif
