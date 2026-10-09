#include "factory/OutdoorPartsFactory.h"

#include "part/AckermannBase.h"
#include "part/GpsLocalizer.h"
#include "part/Lidar3D.h"
#include "part/ThermalCamera.h"

std::unique_ptr<Lidar> OutdoorPartsFactory::createLidar() const
{
	return std::make_unique<Lidar3D>();
}

std::unique_ptr<Localizer> OutdoorPartsFactory::createLocalizer() const
{
	return std::make_unique<GpsLocalizer>();
}

std::unique_ptr<DriveBase> OutdoorPartsFactory::createDriveBase() const
{
	return std::make_unique<AckermannBase>();
}

std::unique_ptr<Camera> OutdoorPartsFactory::createCamera() const
{
	return std::make_unique<ThermalCamera>();
}

std::string OutdoorPartsFactory::profile() const
{
	return "실외 캠퍼스형";
}
