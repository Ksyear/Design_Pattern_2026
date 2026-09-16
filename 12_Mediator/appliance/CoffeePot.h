#ifndef APPLIANCE_COFFEE_POT_H
#define APPLIANCE_COFFEE_POT_H

#include <string>

#include "appliance/Appliance.h"

class CoffeePot : public Appliance {
public:
	CoffeePot();
	void doAction(const std::string& action) override;
};

#endif
