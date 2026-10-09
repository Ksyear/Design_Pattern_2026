#ifndef PART_LIDAR2D_H
#define PART_LIDAR2D_H

#include "part/Lidar.h"

class Lidar2D : public Lidar {
public:
	std::string spec() const override;
	std::string topic() const override;
};

#endif
