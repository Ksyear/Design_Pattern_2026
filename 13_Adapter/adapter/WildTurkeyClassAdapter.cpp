#include "adapter/WildTurkeyClassAdapter.h"

void WildTurkeyClassAdapter::quack() const {
	WildTurkey::gobble();
}

void WildTurkeyClassAdapter::fly() const {
	for (int i = 0; i < 5; ++i) WildTurkey::fly();
}
