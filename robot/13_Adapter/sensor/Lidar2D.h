#ifndef SENSOR_LIDAR2D_H
#define SENSOR_LIDAR2D_H

#include "sensor/RangeSensor.h"

// 처음부터 표준 형식으로 내보내는 센서 - 어댑터가 필요 없다
class Lidar2D : public RangeSensor {
public:
	LaserScan scan() const override;
	std::string name() const override;
};

#endif
