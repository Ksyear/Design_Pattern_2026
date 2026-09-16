#ifndef MEDIATOR_MEDIATOR_H
#define MEDIATOR_MEDIATOR_H

#include <string>

class Appliance;   // 전방 선언 - 중재자도 구상 가전을 알 필요는 없다

// Mediator 인터페이스
//
// 핵심: 객체끼리 직접 부르지 못하게 막고, 전부 중재자를 거치게 한다.
//       - 중재자 도입 전: 알람이 커피포트를 알고, 커피포트가 달력을 알고... (N:N)
//       - 도입 후: 각 가전은 중재자 하나만 안다 (N:1)
class Mediator {
public:
	virtual ~Mediator() = default;
	virtual void notify(Appliance* sender, const std::string& event) = 0;
};

#endif
