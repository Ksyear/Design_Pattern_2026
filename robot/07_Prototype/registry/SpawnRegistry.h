#ifndef REGISTRY_SPAWNREGISTRY_H
#define REGISTRY_SPAWNREGISTRY_H

#include <map>
#include <memory>
#include <string>

#include "spec/RobotSpec.h"

// 설정이 끝난 견본을 이름으로 들고 있다가, 달라고 하면 복제해서 내준다.
//
// 이 클래스에는 DeliveryBot / PatrolBot 이라는 이름이 없다.
// 등록만 해 주면 새 기종이 늘어나도 이 파일은 그대로다.
// (Gazebo 의 모델 데이터베이스, nav2 의 로봇 프로필 파일이 하는 일)
class SpawnRegistry {
public:
	// 견본의 소유권은 레지스트리가 갖는다
	void registerPrototype(const std::string& key, std::unique_ptr<RobotSpec> prototype);

	// 복제해서 위치만 찍어 돌려준다. 없는 키면 nullptr.
	std::unique_ptr<RobotSpec> spawn(const std::string& key,
	                                 const std::string& namespaceName,
	                                 double x, double y) const;

	void listPrototypes() const;

private:
	std::map<std::string, std::unique_ptr<RobotSpec>> prototypes_;
};

#endif
