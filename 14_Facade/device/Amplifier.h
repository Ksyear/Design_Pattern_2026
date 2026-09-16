#ifndef DEVICE_AMPLIFIER_H
#define DEVICE_AMPLIFIER_H

// Subsystem : 자기 일만 안다. 퍼사드의 존재를 모른다.
class Amplifier {
public:
	void on();
	void off();
	void setStreamingPlayer();
	void setSurroundSound();
	void setVolume(int level);
};

#endif
