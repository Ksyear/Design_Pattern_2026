#ifndef MSG_BATTERYSTATE_H
#define MSG_BATTERYSTATE_H

struct BatteryState {
	double percentage = 1.0;
	double voltage = 24.0;
	double current = -2.0;
};

#endif
