#ifndef REMOTE_REMOTE_CONTROL_H
#define REMOTE_REMOTE_CONTROL_H

#include <memory>

#include "tv/TV.h"

// Abstraction : 고수준, 구현에 위임만 한다.
//
// 핵심: 독립적으로 변하는 두 축을 각각의 계층구조로 쪼개고, 구성으로 연결한다.
//       - 추상화(Abstraction) 축: 리모컨 종류 (기본형, 프리미엄)  -> remote/
//       - 구현(Implementation) 축: TV 종류 (소니, LG)             -> tv/
//       두 축을 상속으로 엮으면 2 x 2 = 4개 클래스가 필요하고, 축이 늘 때마다 곱해진다.
class RemoteControl {
public:
	explicit RemoteControl(std::unique_ptr<TV> tv);
	virtual ~RemoteControl() = default;

	virtual void on();
	virtual void off();
	virtual void setChannel(int channel);

	void nextChannel();
	void previousChannel();

	// 실행 중에 TV를 갈아끼울 수 있다 - 상속으로 엮었다면 불가능
	void setTV(std::unique_ptr<TV> tv);

protected:
	// PremiumRemote 가 RemoteControl::setChannel 을 부를 때 읽는 값
	int channel_ = 1;

private:
	// 구현 축은 기반 클래스만 만진다 - 파생 리모컨은 TV 를 직접 건드릴 이유가 없다
	std::unique_ptr<TV> tv_;
};

#endif
