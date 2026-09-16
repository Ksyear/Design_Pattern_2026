#include "remote/PremiumRemote.h"

#include <iostream>

void PremiumRemote::setChannel(int channel) {
	RemoteControl::setChannel(channel);
	std::cout << "  [프리미엄] 채널 " << channel << " 정보를 화면에 표시\n";
}

void PremiumRemote::mute() {
	std::cout << "  [프리미엄] 음소거\n";
}

void PremiumRemote::addFavorite() {
	favorite_ = channel_;
	std::cout << "  [프리미엄] 채널 " << favorite_ << "을(를) 즐겨찾기에 저장\n";
}

void PremiumRemote::goFavorite() {
	if (favorite_ > 0) setChannel(favorite_);
}
