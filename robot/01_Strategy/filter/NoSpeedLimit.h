#ifndef FILTER_NOSPEEDLIMIT_H
#define FILTER_NOSPEEDLIMIT_H

#include "filter/SpeedFilter.h"

// 아무것도 하지 않는 필터 - 기본값 자리
class NoSpeedLimit : public SpeedFilter {
public:
	Twist apply(const Twist& raw) const override;
	std::string name() const override;
};

#endif
