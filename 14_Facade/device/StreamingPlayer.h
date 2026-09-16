#ifndef DEVICE_STREAMING_PLAYER_H
#define DEVICE_STREAMING_PLAYER_H

#include <string>

// Subsystem : 자기 일만 안다. 퍼사드의 존재를 모른다.
class StreamingPlayer {
public:
	void on();
	void off();
	void play(const std::string& movie);
	void stop();
};

#endif
