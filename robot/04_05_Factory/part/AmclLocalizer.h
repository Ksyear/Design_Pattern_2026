#ifndef PART_AMCLLOCALIZER_H
#define PART_AMCLLOCALIZER_H

#include "part/Localizer.h"

class AmclLocalizer : public Localizer {
public:
	std::string spec() const override;
	std::string frame() const override;
};

#endif
