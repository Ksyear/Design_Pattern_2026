#ifndef FACTORY_PARTSFACTORY_H
#define FACTORY_PARTSFACTORY_H

#include <memory>
#include <string>

#include "part/Camera.h"
#include "part/DriveBase.h"
#include "part/Lidar.h"
#include "part/Localizer.h"

class PartsFactory {
public:
	virtual ~PartsFactory() = default;

	virtual std::unique_ptr<Lidar> createLidar() const = 0;
	virtual std::unique_ptr<Localizer> createLocalizer() const = 0;
	virtual std::unique_ptr<DriveBase> createDriveBase() const = 0;
	virtual std::unique_ptr<Camera> createCamera() const = 0;

	virtual std::string profile() const = 0;
};

#endif
