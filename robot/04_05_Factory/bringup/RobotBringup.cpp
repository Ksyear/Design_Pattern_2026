#include "bringup/RobotBringup.h"

#include <iostream>
#include <utility>

RobotBringup::RobotBringup(std::string site, std::unique_ptr<PartsFactory> parts)
	: site_(std::move(site)), parts_(std::move(parts))
{
}

std::unique_ptr<RobotPlatform> RobotBringup::launch(const std::string& mission) const
{
	std::cout << "  [" << site_ << "] bringup 시작 - 임무 " << mission << "\n";

	std::unique_ptr<RobotPlatform> robot = createRobot(mission);
	if (!robot) {
		std::cout << "    이 현장에는 이 임무를 맡을 기종이 없다 - 중단\n";
		return nullptr;
	}
	std::cout << "    [팩토리 메소드] 기종       -> " << robot->name() << "\n";

	std::cout << "    [추상 팩토리]   부품 한 벌 -> " << parts_->profile() << "\n";
	robot->assemble(*parts_);

	robot->configure();
	robot->printBom();
	robot->planPath();

	std::cout << "    활성 완료 : " << robot->name() << "\n";
	return robot;
}
