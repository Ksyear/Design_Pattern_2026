#ifndef FILTER_MEDIANFILTER_H
#define FILTER_MEDIANFILTER_H

#include "filter/ScanFilter.h"

class MedianFilter : public ScanFilter {
public:
	using ScanFilter::ScanFilter;

	LaserScan read() const override;
	double latencyMs() const override;
	std::string pipeline() const override;
};

#endif
