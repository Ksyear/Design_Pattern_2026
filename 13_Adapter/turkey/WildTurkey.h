#ifndef TURKEY_WILD_TURKEY_H
#define TURKEY_WILD_TURKEY_H

#include "turkey/Turkey.h"

class WildTurkey : public Turkey {
public:
	void gobble() const override;
	void fly() const override;
};

#endif
