#include "filter/RangeClamp.h"

#include <algorithm>
#include <utility>

RangeClamp::RangeClamp(std::unique_ptr<ScanSource> source, double minRange, double maxRange)
	: ScanFilter(std::move(source)), minRange_(minRange), maxRange_(maxRange)
{
}

LaserScan RangeClamp::read() const
{
	LaserScan scan = source_->read();
	for (double& r : scan.ranges) {
		r = std::clamp(r, minRange_, maxRange_);
	}
	return scan;
}

double RangeClamp::latencyMs() const
{
	return source_->latencyMs() + 0.3;
}

std::string RangeClamp::pipeline() const
{
	return source_->pipeline() + " + clamp";
}
