#ifndef MSG_TYPES_H
#define MSG_TYPES_H

struct Twist {
	double linear_x = 0.0;
	double angular_z = 0.0;
};

struct Pose2D {
	double x = 0.0;
	double y = 0.0;
	double yaw = 0.0;
};

struct LaserScan {
	double front_range_m = 10.0;
};

#endif
