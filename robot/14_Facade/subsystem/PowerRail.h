#ifndef SUBSYSTEM_POWERRAIL_H
#define SUBSYSTEM_POWERRAIL_H

// 전원 레일 - 24V 를 각 장치에 공급한다
class PowerRail {
public:
	void enable24V();
	void disable24V();
	bool isOn() const;

private:
	bool on_ = false;
};

#endif
