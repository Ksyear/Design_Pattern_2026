#ifndef APPLIANCE_APPLIANCE_H
#define APPLIANCE_APPLIANCE_H

#include <string>

class Mediator;   // 전방 선언 - 가전은 중재자의 '이름'만 알면 된다

// Component
// 가전은 중재자만 알고, 다른 가전은 전혀 모른다.
// 이 헤더에 Alarm 도 CoffeePot 도 등장하지 않는 것이 N:N -> N:1 의 증거다.
class Appliance {
public:
	explicit Appliance(std::string name);
	virtual ~Appliance() = default;

	void setMediator(Mediator* m);
	const std::string& name() const;

	// 중재자가 시키는 일
	virtual void doAction(const std::string& action) = 0;

protected:
	// 상태가 바뀌면 중재자에게만 알린다
	void notifyMediator(const std::string& event);

private:
	// 서브클래스는 name() 접근자로만 읽는다 - 직접 대입할 통로를 두지 않는다
	std::string name_;
	Mediator* mediator_ = nullptr;
};

#endif
