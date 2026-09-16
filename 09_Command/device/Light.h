#ifndef DEVICE_LIGHT_H
#define DEVICE_LIGHT_H

#include <string>

// Receiver : 실제 일을 하는 객체. 커맨드가 있다는 사실조차 모른다.
class Light {
public:
	explicit Light(std::string location);
	void on();
	void off();

private:
	std::string location_;
};

#endif
