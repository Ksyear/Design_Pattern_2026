#ifndef FILTER_DROPOUTLIER_H
#define FILTER_DROPOUTLIER_H

#include "filter/ScanFilter.h"

class DropOutlier : public ScanFilter {
public:
	explicit DropOutlier(std::unique_ptr<ScanSource> source, double maxValid = 30.0);

	LaserScan read() const override;
	double latencyMs() const override;
	std::string pipeline() const override;

private:
	double maxValid_;
};

#endif
