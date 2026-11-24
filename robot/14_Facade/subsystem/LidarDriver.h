#ifndef SUBSYSTEM_LIDARDRIVER_H
#define SUBSYSTEM_LIDARDRIVER_H

// 라이다 - 모터가 규정 회전수에 올라야 유효한 스캔이 나온다
class LidarDriver {
public:
	void spinUp();
	void spinDown();
};

#endif
