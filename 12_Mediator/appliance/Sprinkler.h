#ifndef APPLIANCE_SPRINKLER_H
#define APPLIANCE_SPRINKLER_H

#include <string>

#include "appliance/Appliance.h"

class Sprinkler : public Appliance {
public:
	Sprinkler();
	void doAction(const std::string& action) override;
};

#endif
