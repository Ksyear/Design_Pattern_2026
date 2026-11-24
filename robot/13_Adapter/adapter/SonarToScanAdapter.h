#ifndef ADAPTER_SONARTOSCANADAPTER_H
#define ADAPTER_SONARTOSCANADAPTER_H

#include <memory>

#include "legacy/SerialSonarArray.h"
#include "sensor/RangeSensor.h"

// 객체 어댑터 - 낡은 보드를 품고(has-a) 표준 형식으로 번역한다.
//
// 하는 일은 번역뿐이다 : 단위(cm->m), 실패 표현(-1 -> 0.0), 호출 방식(하나씩 -> 배열).
// 상위 코드는 이것이 초음파인지 라이다인지 모른다.
//
// ROS 2 에도 이런 어댑터가 노드 형태로 존재한다.
//   pointcloud_to_laserscan, depthimage_to_laserscan, range 메시지 변환 노드 등.
//   "센서는 그대로 두고 형식만 맞춰 주는 노드" 가 전부 이 패턴이다.
class SonarToScanAdapter : public RangeSensor {
public:
	explicit SonarToScanAdapter(std::unique_ptr<SerialSonarArray> board);

	LaserScan scan() const override;
	std::string name() const override;

private:
	std::unique_ptr<SerialSonarArray> board_;  // 소유한다
};

#endif
