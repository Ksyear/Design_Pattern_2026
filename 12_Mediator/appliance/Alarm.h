#ifndef APPLIANCE_ALARM_H
#define APPLIANCE_ALARM_H

#include <string>

#include "appliance/Appliance.h"

class Alarm : public Appliance {
public:
	Alarm();
	void ring();
	void doAction(const std::string& action) override;
};

#endif
