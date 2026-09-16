// 퍼사드 패턴 (Facade) - 헤드 퍼스트 7장 홈시어터
//
// 이 파일은 "조립과 호출"만 한다. 클래스는 기능별 폴더에 나뉘어 있다.
//   device/  Subsystem - 앰프/튜너/플레이어/프로젝터/조명/스크린/팝콘기계 7개
//   facade/  창구      - HomeTheaterFacade.*
//
// device/ 안의 7개는 서로도, 퍼사드도 모른다.
// 클라이언트가 facade/ 하나만 include 하면 되는 것이 최소 지식 원칙의 결과다.
#include <iostream>

#include "device/Amplifier.h"
#include "device/PopcornPopper.h"
#include "device/Projector.h"
#include "device/Screen.h"
#include "device/StreamingPlayer.h"
#include "device/TheaterLights.h"
#include "device/Tuner.h"
#include "facade/HomeTheaterFacade.h"

int main() {
	Amplifier amp;
	Tuner tuner;
	StreamingPlayer player;
	Projector projector;
	Screen screen;
	TheaterLights lights;
	PopcornPopper popper;

	HomeTheaterFacade homeTheater(amp, tuner, player, projector, screen, lights, popper);

	homeTheater.watchMovie("인디아나 존스: 레이더스");
	std::cout << '\n';
	homeTheater.endMovie();

	std::cout << "\n--- 퍼사드를 무시하고 직접 써도 된다 ---\n";
	tuner.on();
	amp.on();

	return 0;
}
