#include "adapter/SonarClassAdapter.h"

SonarClassAdapter::SonarClassAdapter(const char* device)
{
	openPort(device);  // 물려받은 기능을 직접 부른다 (포인터 경유가 없다)
}

LaserScan SonarClassAdapter::scan() const
{
	LaserScan out;
	out.frameId = "sonar_link";
	const int n = sensorCount();
	for (int i = 0; i < n; ++i) {
		const int cm = pingCentimeters(i);
		out.ranges.push_back(cm < 0 ? 0.0 : cm / 100.0);
	}
	return out;
}

std::string SonarClassAdapter::name() const
{
	return "SonarArray (클래스 어댑터)";
}
