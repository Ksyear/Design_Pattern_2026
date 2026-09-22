#ifndef FILTER_SPEEDFILTER_H
#define FILTER_SPEEDFILTER_H

#include <string>

#include "msg/Types.h"

class SpeedFilter {
public:
	virtual ~SpeedFilter() = default;

	virtual Twist apply(const Twist& raw) const = 0;
	virtual std::string name() const = 0;
};

#endif
