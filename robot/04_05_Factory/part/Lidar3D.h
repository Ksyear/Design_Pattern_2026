#ifndef PART_LIDAR3D_H
#define PART_LIDAR3D_H

#include "part/Lidar.h"

class Lidar3D : public Lidar {
public:
	std::string spec() const override;
	std::string topic() const override;
};

#endif
