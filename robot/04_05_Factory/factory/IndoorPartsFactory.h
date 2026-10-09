#ifndef FACTORY_INDOORPARTSFACTORY_H
#define FACTORY_INDOORPARTSFACTORY_H

#include "factory/PartsFactory.h"

class IndoorPartsFactory : public PartsFactory {
public:
	std::unique_ptr<Lidar> createLidar() const override;
	std::unique_ptr<Localizer> createLocalizer() const override;
	std::unique_ptr<DriveBase> createDriveBase() const override;
	std::unique_ptr<Camera> createCamera() const override;
	std::string profile() const override;
};

#endif
