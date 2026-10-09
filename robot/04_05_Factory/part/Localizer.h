#ifndef PART_LOCALIZER_H
#define PART_LOCALIZER_H

#include <string>

class Localizer {
public:
	virtual ~Localizer() = default;
	virtual std::string spec() const = 0;
	virtual std::string frame() const = 0;
};

#endif
