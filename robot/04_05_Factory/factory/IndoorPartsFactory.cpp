#include "factory/IndoorPartsFactory.h"

#include "part/AmclLocalizer.h"
#include "part/DiffDriveBase.h"
#include "part/Lidar2D.h"
#include "part/RgbdCamera.h"

std::unique_ptr<Lidar> IndoorPartsFactory::createLidar() const
{
	return std::make_unique<Lidar2D>();
}

std::unique_ptr<Localizer> IndoorPartsFactory::createLocalizer() const
{
	return std::make_unique<AmclLocalizer>();
}

std::unique_ptr<DriveBase> IndoorPartsFactory::createDriveBase() const
{
	return std::make_unique<DiffDriveBase>();
}

std::unique_ptr<Camera> IndoorPartsFactory::createCamera() const
{
	return std::make_unique<RgbdCamera>();
}

std::string IndoorPartsFactory::profile() const
{
	return "실내 창고형";
}
