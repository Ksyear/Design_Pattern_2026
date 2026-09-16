#ifndef TV_L_G_H
#define TV_L_G_H

#include <string>

#include "tv/TV.h"

// Concrete Implementation : 구현 축의 한 갈래
class LG : public TV {
public:
	void on() override;
	void off() override;
	void tuneChannel(int channel) override;
	std::string brand() const override;
};

#endif
