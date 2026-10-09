#ifndef PART_GPSLOCALIZER_H
#define PART_GPSLOCALIZER_H

#include "part/Localizer.h"

class GpsLocalizer : public Localizer {
public:
	std::string spec() const override;
	std::string frame() const override;
};

#endif
