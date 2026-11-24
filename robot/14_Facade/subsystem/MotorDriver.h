#ifndef SUBSYSTEM_MOTORDRIVER_H
#define SUBSYSTEM_MOTORDRIVER_H

// 모터 드라이버 - 순서를 틀리면 위험한 장치.
// 브레이크를 풀기 전에 전원이 들어와 있어야 하고,
// 끌 때는 반드시 브레이크를 먼저 걸어야 한다.
class MotorDriver {
public:
	void enable();
	void releaseBrake();
	void engageBrake();
	void disable();
};

#endif
