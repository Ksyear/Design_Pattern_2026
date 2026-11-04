// 프로토타입 패턴 (Prototype) - 같은 기종 로봇을 여러 대 스폰하기
//
// 책의 몬스터 레지스트리(../../07_Prototype)와 같은 패턴이다.
//   Monster         -> RobotSpec
//   MonsterRegistry -> SpawnRegistry
//   clone()         -> clone()
//
// 로봇에서의 자리
//   Gazebo 에 같은 기종을 열 대 띄울 때, URDF 를 열 번 파싱하고
//   센서 파라미터를 열 번 조립하는 대신 설정이 끝난 견본 하나를 복제한다.
//   fleet 관리에서 "기본 프로필 + 개체별 차이(네임스페이스, 초기 위치)" 구조가 흔하다.
//
// 폴더 지도
//   spec/      Prototype - RobotSpec.*(공통) + 구상 기종 2개
//   registry/  견본 보관소 - SpawnRegistry.*
#include <iostream>
#include <memory>
#include <vector>

#include "registry/SpawnRegistry.h"
#include "spec/DeliveryBot.h"
#include "spec/PatrolBot.h"

int main()
{
	SpawnRegistry registry;

	std::cout << "===== 1. 견본 등록 =====\n";
	registry.registerPrototype("delivery", std::make_unique<DeliveryBot>());
	registry.registerPrototype("patrol", std::make_unique<PatrolBot>());

	// 견본 자체를 손봐 두면 이후 스폰되는 개체가 전부 그 설정을 물려받는다.
	// "기본 프로필을 고친다" 가 이 한 줄이 된다.
	auto tuned = std::make_unique<DeliveryBot>();
	tuned->addSensor("cargo_weight_sensor");
	registry.registerPrototype("delivery_v2", std::move(tuned));

	std::cout << "\n===== 2. 등록된 견본 =====\n";
	registry.listPrototypes();

	std::cout << "\n===== 3. 세 대 스폰 - 위치와 네임스페이스만 다르다 =====\n";
	std::vector<std::unique_ptr<RobotSpec>> fleet;
	fleet.push_back(registry.spawn("delivery", "amr_01", 1.0, 1.0));
	fleet.push_back(registry.spawn("delivery_v2", "amr_02", 3.0, 1.0));
	fleet.push_back(registry.spawn("patrol", "sec_01", 0.0, 7.5));

	for (const std::unique_ptr<RobotSpec>& robot : fleet) {
		robot->describe();
	}

	std::cout << "\n===== 4. 복제본을 고쳐도 견본은 그대로다 (깊은 복사 확인) =====\n";
	fleet.front()->addSensor("bumper");
	std::cout << "  amr_01 에만 범퍼를 달았다\n";
	fleet.front()->describe();
	std::cout << "  견본 delivery 는 :\n";
	registry.spawn("delivery", "check", 0.0, 0.0)->describe();

	std::cout << "\n===== 5. 없는 견본 =====\n";
	if (registry.spawn("drone", "uav_01", 0.0, 0.0) == nullptr) {
		std::cout << "  nullptr 이 돌아왔다 - 호출한 쪽이 확인해야 한다\n";
	}

	// 확인할 것 :
	//   SpawnRegistry 는 DeliveryBot 이라는 이름을 모른다. clone() 만 부른다.
	//   새 기종을 추가할 때 고치는 곳은 main 의 등록 한 줄뿐이다.
	//   멤버가 전부 값 타입이라 깊은 복사가 공짜였다.
	//   만약 RobotSpec 이 원시 포인터를 들고 있었다면 4번 장면에서 견본까지 오염된다.
	return 0;
}
