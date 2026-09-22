#ifndef FILTER_NOSPEEDLIMIT_H
#define FILTER_NOSPEEDLIMIT_H

#include "filter/SpeedFilter.h"

class NoSpeedLimit : public SpeedFilter {
public:
	Twist apply(const Twist& raw) const override;
	std::string name() const override;
};

#endif
