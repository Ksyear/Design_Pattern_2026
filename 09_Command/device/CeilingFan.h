#ifndef DEVICE_CEILING_FAN_H
#define DEVICE_CEILING_FAN_H

#include <string>

// Receiver : 상태(속도)를 가진 장치.
// 상태가 있기 때문에 작업 취소가 '반대 동작'이 아니라 '직전 상태 복구'가 된다.
class CeilingFan {
public:
	enum Speed { Off = 0, Low = 1, Medium = 2, High = 3 };

	explicit CeilingFan(std::string location);
	void setSpeed(Speed s);
	Speed getSpeed() const;

private:
	std::string location_;
	Speed speed_ = Off;
};

#endif
