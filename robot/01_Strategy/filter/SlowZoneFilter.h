#ifndef FILTER_SLOWZONEFILTER_H
#define FILTER_SLOWZONEFILTER_H

#include "filter/SpeedFilter.h"

// 서행 구역 - 선속도 상한을 내린다 (사람이 다니는 복도, 교차로 등)
class SlowZoneFilter : public SpeedFilter {
public:
	explicit SlowZoneFilter(double maxLinearVel = 0.2);

	Twist apply(const Twist& raw) const override;
	std::string name() const override;

private:
	double maxLinearVel_;
};

#endif
