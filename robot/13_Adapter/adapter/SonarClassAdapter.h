#ifndef ADAPTER_SONARCLASSADAPTER_H
#define ADAPTER_SONARCLASSADAPTER_H

#include "legacy/SerialSonarArray.h"
#include "sensor/RangeSensor.h"

// 클래스 어댑터 - 자바에서는 못 만들고 C++ 에서만 되는 형태.
//
//   public RangeSensor    : 상위 코드가 기대하는 형식이 된다 (is-a)
//   private SerialSonarArray : 낡은 보드의 기능을 물려받되 밖으로는 감춘다
//
// 다중 상속이 있어서 가능하다. 자바 구현을 그대로 옮기면 객체 어댑터뿐이지만,
// C++ 에서는 선택지가 하나 더 있다는 것을 보여 주려고 나란히 뒀다.
//
// 어느 쪽을 쓸 것인가
//   객체 어댑터 : 런타임에 대상을 바꿔 끼울 수 있고, 여러 개를 감쌀 수 있다. 대개 이쪽.
//   클래스 어댑터 : 포인터 하나가 덜 들고 오버라이드로 동작을 손볼 수 있지만,
//                   대상이 컴파일 시점에 고정되고 상속 관계가 얽힌다.
class SonarClassAdapter : public RangeSensor, private SerialSonarArray {
public:
	explicit SonarClassAdapter(const char* device);

	LaserScan scan() const override;
	std::string name() const override;
};

#endif
