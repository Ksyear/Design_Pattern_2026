#include "subsystem/Localization.h"

#include <iostream>
#include <string_view>

namespace {
// 로봇에 실려 있다고 치는 지도 (시뮬레이션). 다른 이름은 파일이 없는 것으로 본다.
constexpr std::string_view kInstalledMap = "warehouse_1f.yaml";
}

void Localization::loadMap(const char* mapName)
{
	mapLoaded_ = (mapName == kInstalledMap);
	std::cout << "    [amcl] 지도 로드 : " << mapName << (mapLoaded_ ? "" : "  (파일 없음)") << '\n';
}

void Localization::setInitialPose(double x, double y)
{
	std::cout << "    [amcl] 초기 위치 (" << x << ", " << y << ") 설정\n";
}

bool Localization::waitForConvergence()
{
	std::cout << "    [amcl] 파티클 수렴 확인 - " << (mapLoaded_ ? "OK" : "실패 (지도 없음)") << '\n';
	return mapLoaded_;
}
