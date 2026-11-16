#ifndef DEVICE_MOBILEBASE_H
#define DEVICE_MOBILEBASE_H

// Receiver - 실제로 일하는 쪽. 명령 객체는 이 함수들을 부를 뿐이다.
// ROS 2 로 치면 /cmd_vel 을 받아 바퀴를 돌리는 드라이버 노드.
class MobileBase {
public:
	void driveForward(double meters);
	void turn(double degrees);
	void report() const;

private:
	double x_ = 0.0;
	double y_ = 0.0;
	double headingDeg_ = 0.0;
};

#endif
