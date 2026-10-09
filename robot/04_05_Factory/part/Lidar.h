#ifndef PART_LIDAR_H
#define PART_LIDAR_H

#include <string>

class Lidar {
public:
	virtual ~Lidar() = default;
	virtual std::string spec() const = 0;
	virtual std::string topic() const = 0;
};

#endif
