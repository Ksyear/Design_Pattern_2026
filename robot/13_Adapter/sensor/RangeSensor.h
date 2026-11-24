#ifndef SENSOR_RANGESENSOR_H
#define SENSOR_RANGESENSOR_H

#include <string>

#include "msg/LaserScan.h"

// Target - 상위 코드가 아는 유일한 형식.
//
// 내비게이션 스택은 "거리 센서" 를 이 모양으로만 다룬다.
// 새 센서를 붙일 때마다 내비게이션을 고칠 수는 없으니,
// 안 맞는 센서는 끼워 맞춰 주는 물건이 필요하다. 그것이 어댑터다.
class RangeSensor {
public:
	virtual ~RangeSensor() = default;

	virtual LaserScan scan() const = 0;
	virtual std::string name() const = 0;
};

#endif
