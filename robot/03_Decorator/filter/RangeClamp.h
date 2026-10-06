#ifndef FILTER_RANGECLAMP_H
#define FILTER_RANGECLAMP_H

#include "filter/ScanFilter.h"

class RangeClamp : public ScanFilter {
public:
	RangeClamp(std::unique_ptr<ScanSource> source, double minRange, double maxRange);

	LaserScan read() const override;
	double latencyMs() const override;
	std::string pipeline() const override;

private:
	double minRange_;
	double maxRange_;
};

#endif
