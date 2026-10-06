#ifndef SCAN_SCANSOURCE_H
#define SCAN_SCANSOURCE_H

#include <string>

#include "msg/LaserScan.h"

class ScanSource {
public:
	virtual ~ScanSource() = default;

	virtual LaserScan read() const = 0;

	virtual double latencyMs() const = 0;

	virtual std::string pipeline() const = 0;
};

#endif
