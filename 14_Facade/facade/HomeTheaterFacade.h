#ifndef FACADE_HOME_THEATER_FACADE_H
#define FACADE_HOME_THEATER_FACADE_H

#include <string>

#include "device/Amplifier.h"
#include "device/PopcornPopper.h"
#include "device/Projector.h"
#include "device/Screen.h"
#include "device/StreamingPlayer.h"
#include "device/TheaterLights.h"
#include "device/Tuner.h"

// Facade
//
// 핵심: 복잡한 서브시스템 앞에 '단순한 고수준 인터페이스'를 하나 둔다.
//       퍼사드는 기능을 감추지 않는다 - 필요하면 서브시스템을 직접 써도 된다.
//
// 관련 원칙: 최소 지식 원칙 (Law of Demeter, "진짜 절친에게만 이야기해야 한다")
//   퍼사드가 없으면 클라이언트가 7개 클래스와 직접 얽힌다.
//   이 헤더가 7개를 모두 include 한다는 점이 '얽힘을 여기로 모았다'는 뜻이다.
class HomeTheaterFacade {
public:
	HomeTheaterFacade(Amplifier& amp, Tuner& tuner, StreamingPlayer& player, Projector& projector,
	                  Screen& screen, TheaterLights& lights, PopcornPopper& popper);

	// 고수준 메소드 하나로 12단계를 대신한다
	void watchMovie(const std::string& movie);
	void endMovie();

	// 퍼사드는 서브시스템을 '가리지' 않는다 - 라디오만 쓰고 싶으면 이런 메소드를 더 둘 수도 있다
	void listenToRadio();

private:
	Amplifier& amp_;
	Tuner& tuner_;
	StreamingPlayer& player_;
	Projector& projector_;
	Screen& screen_;
	TheaterLights& lights_;
	PopcornPopper& popper_;
};

#endif
