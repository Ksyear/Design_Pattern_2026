#include "platform/DeliveryRobot.h"

void DeliveryRobot::assemble(const PartsFactory& parts)
{
	lidar_ = parts.createLidar();
	localizer_ = parts.createLocalizer();
	driveBase_ = parts.createDriveBase();
}
