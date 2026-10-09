#ifndef PART_CAMERA_H
#define PART_CAMERA_H

#include <string>

class Camera {
public:
	virtual ~Camera() = default;
	virtual std::string spec() const = 0;
	virtual std::string topic() const = 0;
};

#endif
