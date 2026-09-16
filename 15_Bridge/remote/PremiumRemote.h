#ifndef REMOTE_PREMIUM_REMOTE_H
#define REMOTE_PREMIUM_REMOTE_H

#include "remote/RemoteControl.h"

// Refined Abstraction : 고수준 로직의 변형.
// TV 가 몇 종류로 늘어나든 이 클래스는 손대지 않는다.
class PremiumRemote : public RemoteControl {
public:
	using RemoteControl::RemoteControl;

	void setChannel(int channel) override;

	void mute();
	void addFavorite();
	void goFavorite();

private:
	int favorite_ = 0;
};

#endif
