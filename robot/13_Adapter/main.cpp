// 어댑터 패턴 (Adapter) - 낡은 초음파 보드를 표준 거리 센서로
//
// 책의 칠면조를 오리로(../../13_Adapter)와 같은 패턴이다.
//   Duck            -> RangeSensor        (상위 코드가 아는 형식)
//   Turkey          -> SerialSonarArray   (형식이 안 맞는 기존 물건)
//   TurkeyAdapter   -> SonarToScanAdapter (사이에 끼워 넣는 번역기)
//
// 로봇에서의 자리
//   센서는 벤더마다 단위도 실패 표현도 호출 방식도 다르다.
//   그때마다 내비게이션을 고칠 수는 없으니 형식을 맞춰 주는 층을 하나 둔다.
//   ROS 2 의 pointcloud_to_laserscan, depthimage_to_laserscan 같은 노드가 정확히 이것이다.
//
// 이 폴더에는 C++ 에서만 가능한 형태도 같이 뒀다 (클래스 어댑터, 다중 상속).
//
// 폴더 지도
//   msg/      표준 메시지 - LaserScan
//   sensor/   Target     - RangeSensor.h + 이미 표준인 Lidar2D
//   legacy/   Adaptee    - SerialSonarArray (고칠 수 없다고 가정)
//   adapter/  Adapter    - 객체 어댑터 / 클래스 어댑터 두 가지
#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>

#include "adapter/SonarClassAdapter.h"
#include "adapter/SonarToScanAdapter.h"
#include "legacy/SerialSonarArray.h"
#include "sensor/Lidar2D.h"

namespace {

// 상위 코드 - RangeSensor 하나만 안다.
// 센서가 무엇이든, 어댑터를 거쳤든 아니든 이 함수는 바뀌지 않는다.
void runObstacleCheck(const RangeSensor& sensor)
{
	const LaserScan data = sensor.scan();
	std::cout << "  [" << sensor.name() << "] frame=" << data.frameId << "  ranges =";
	for (double r : data.ranges) {
		std::cout << ' ' << std::fixed << std::setprecision(2) << r;
	}
	constexpr double kNoValid = 1e9;
	double nearest = kNoValid;
	for (double r : data.ranges) {
		if (r > 0.0 && r < nearest) {
			nearest = r;
		}
	}
	if (nearest == kNoValid) {  // 유효값이 하나도 없다 = 고장. 빈 길로 읽으면 안 된다
		std::cout << "\n      유효한 측정값 없음 -> 정지\n\n";
		return;
	}
	std::cout << "\n      최단 거리 " << nearest << "m -> "
	          << (nearest < 1.0 ? "감속" : "정상 주행") << "\n\n";
}

}  // namespace

int main()
{
	std::cout << "===== 1. 처음부터 표준 형식인 센서 =====\n";
	runObstacleCheck(Lidar2D{});

	std::cout << "===== 2. 낡은 보드를 직접 쓰면 이렇게 생겼다 =====\n";
	SerialSonarArray raw;
	raw.openPort("/dev/ttyS1");
	std::cout << "    pingCentimeters(0) = " << raw.pingCentimeters(0) << " (cm)\n";
	std::cout << "    pingCentimeters(2) = " << raw.pingCentimeters(2) << " (실패를 -1 로)\n";
	std::cout << "    -> 단위도 실패 표현도 호출 방식도 다르다\n\n";

	std::cout << "===== 3. 객체 어댑터를 끼우면 표준 센서가 된다 =====\n";
	auto board = std::make_unique<SerialSonarArray>();
	board->openPort("/dev/ttyS1");
	SonarToScanAdapter adapted(std::move(board));
	runObstacleCheck(adapted);

	std::cout << "===== 4. 클래스 어댑터 (C++ 다중 상속) =====\n";
	runObstacleCheck(SonarClassAdapter{"/dev/ttyS2"});

	std::cout << "===== 5. 상위 코드는 셋을 구분하지 않는다 =====\n";
	std::vector<std::unique_ptr<RangeSensor>> sensors;
	sensors.push_back(std::make_unique<Lidar2D>());
	sensors.push_back(std::make_unique<SonarClassAdapter>("/dev/ttyS2"));
	for (const std::unique_ptr<RangeSensor>& s : sensors) {
		runObstacleCheck(*s);
	}

	std::cout << "===== 6. 응답 없는 보드 - 실패를 빈 길로 읽지 않는다 =====\n";
	// openPort() 를 빠뜨린 보드는 전부 -1 을 주고, 어댑터는 그것을 전부 0.0 으로 번역한다.
	runObstacleCheck(SonarToScanAdapter{std::make_unique<SerialSonarArray>()});

	// 확인할 것 :
	//   SerialSonarArray 는 한 줄도 고치지 않았다.
	//   runObstacleCheck 도 어댑터 때문에 고친 줄은 없다.
	//   새로 생긴 것은 그 사이의 번역기 하나뿐이다.
	//   6번 장면 : 번역은 "측정 실패" 라는 의미까지 흐린다. 그래서 상위 코드는 유효값이 없으면 멈춘다.
	return 0;
}
