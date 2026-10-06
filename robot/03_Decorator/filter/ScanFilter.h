#ifndef FILTER_SCANFILTER_H
#define FILTER_SCANFILTER_H

#include <memory>

#include "scan/ScanSource.h"

class ScanFilter : public ScanSource {
public:
	explicit ScanFilter(std::unique_ptr<ScanSource> source);

protected:
	std::unique_ptr<ScanSource> source_;
};

#endif
