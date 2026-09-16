// 브리지 패턴 (Bridge) - 헤드 퍼스트 14장 리모컨 x TV
//
// 이 파일은 "조립과 호출"만 한다. 두 축이 곧 두 폴더다.
//   remote/  추상화 축 - RemoteControl.*(기본) + PremiumRemote.*(변형)
//   tv/      구현 축   - TV.h(인터페이스) + Sony.*, LG.*
//
// remote/ 는 TV 인터페이스만 알고 Sony 도 LG 도 모른다.
// 한쪽 폴더에 파일을 더 넣어도 다른 폴더는 그대로다 -> M+N 클래스로 끝난다 (M*N 이 아니다).
#include <iostream>
#include <memory>

#include "remote/PremiumRemote.h"
#include "remote/RemoteControl.h"
#include "tv/LG.h"
#include "tv/Sony.h"

int main() {
	std::cout << "--- 기본 리모컨 + 소니 TV ---\n";
	RemoteControl basic(std::make_unique<Sony>());
	basic.on();
	basic.setChannel(7);
	basic.nextChannel();
	basic.off();

	std::cout << "\n--- 프리미엄 리모컨 + LG TV ---\n";
	PremiumRemote premium(std::make_unique<LG>());
	premium.on();
	premium.setChannel(11);
	premium.addFavorite();
	premium.nextChannel();
	premium.goFavorite();
	premium.mute();

	std::cout << "\n--- 같은 리모컨에 TV만 교체 ---\n";
	premium.setTV(std::make_unique<Sony>());
	premium.setChannel(3);

	// 리모컨 종류 M개 x TV 종류 N개 = M+N 클래스로 끝난다 (M*N 이 아니다)
	return 0;
}
