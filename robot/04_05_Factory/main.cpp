#include <iostream>
#include <memory>
#include <vector>

#include "bringup/CampusBringup.h"
#include "bringup/WarehouseBringup.h"

int main()
{
	const WarehouseBringup warehouse;
	const CampusBringup campus;

	std::vector<std::unique_ptr<RobotPlatform>> fleet;

	std::cout << "===== 1. 창고 배송 로봇 =====\n";
	fleet.push_back(warehouse.launch("delivery"));

	std::cout << "\n===== 2. 임무만 바꾼다 - 팩토리 메소드 축 (카메라가 붙는다) =====\n";
	fleet.push_back(warehouse.launch("patrol"));

	std::cout << "\n===== 3. 현장만 바꾼다 - 추상 팩토리 축 (부품이 한 벌째 바뀐다) =====\n";
	fleet.push_back(campus.launch("patrol"));

	std::cout << "\n===== 4. 현장이 모르는 임무 =====\n";
	std::unique_ptr<RobotPlatform> mower = campus.launch("mowing");
	std::cout << "  결과 : " << (mower ? "생성됨" : "nullptr - 아무것도 만들지 않았다") << "\n";

	std::cout << "\n===== 5. 가동 중인 로봇 " << fleet.size() << "대 =====\n";
	for (const std::unique_ptr<RobotPlatform>& robot : fleet) {
		std::cout << "  " << robot->name() << "\n";
		robot->planPath();
	}

	return 0;
}
