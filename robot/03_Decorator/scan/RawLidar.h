#ifndef SCAN_RAWLIDAR_H
#define SCAN_RAWLIDAR_H

#include "scan/ScanSource.h"

class RawLidar : public ScanSource {
public:
	LaserScan read() const override;
	double latencyMs() const override;
	std::string pipeline() const override;
};

#endif
