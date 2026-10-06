#include "filter/DropOutlier.h"

#include <utility>

DropOutlier::DropOutlier(std::unique_ptr<ScanSource> source, double maxValid)
	: ScanFilter(std::move(source)), maxValid_(maxValid)
{
}

LaserScan DropOutlier::read() const
{
	LaserScan scan = source_->read();
	for (std::size_t i = 0; i < scan.ranges.size(); ++i) {
		const double v = scan.ranges[i];
		if (v > 0.0 && v <= maxValid_) {
			continue;
		}
		scan.ranges[i] = (i > 0) ? scan.ranges[i - 1] : maxValid_;
	}
	return scan;
}

double DropOutlier::latencyMs() const
{
	return source_->latencyMs() + 0.8;
}

std::string DropOutlier::pipeline() const
{
	return source_->pipeline() + " + drop_outlier";
}
