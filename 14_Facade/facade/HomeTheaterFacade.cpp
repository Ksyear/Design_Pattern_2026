#include "facade/HomeTheaterFacade.h"

#include <iostream>

HomeTheaterFacade::HomeTheaterFacade(Amplifier& amp, Tuner& tuner, StreamingPlayer& player,
                                     Projector& projector, Screen& screen, TheaterLights& lights,
                                     PopcornPopper& popper)
	: amp_(amp), tuner_(tuner), player_(player), projector_(projector), screen_(screen),
	  lights_(lights), popper_(popper) {}

void HomeTheaterFacade::watchMovie(const std::string& movie) {
	std::cout << "영화 볼 준비 중...\n";
	popper_.on();
	popper_.pop();
	lights_.dim(10);
	screen_.down();
	projector_.on();
	projector_.wideScreenMode();
	amp_.on();
	amp_.setStreamingPlayer();
	amp_.setSurroundSound();
	amp_.setVolume(5);
	player_.on();
	player_.play(movie);
}

void HomeTheaterFacade::endMovie() {
	std::cout << "홈시어터를 끄는 중...\n";
	popper_.off();
	lights_.on();
	screen_.up();
	projector_.off();
	amp_.off();
	player_.stop();
	player_.off();
}

void HomeTheaterFacade::listenToRadio() {
	std::cout << "라디오 켜는 중...\n";
	tuner_.on();
	amp_.on();
	amp_.setVolume(5);
}
