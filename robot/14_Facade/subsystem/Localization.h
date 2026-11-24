#ifndef SUBSYSTEM_LOCALIZATION_H
#define SUBSYSTEM_LOCALIZATION_H

// 측위 - 지도를 올리고 초기 위치를 잡아야 수렴한다
class Localization {
public:
	void loadMap(const char* mapName);
	void setInitialPose(double x, double y);
	bool waitForConvergence();  // 지도가 없으면 수렴하지 못한다

private:
	bool mapLoaded_ = false;
};

#endif
