#include "registry/SpawnRegistry.h"

#include <iostream>
#include <utility>

void SpawnRegistry::registerPrototype(const std::string& key, std::unique_ptr<RobotSpec> prototype)
{
	if (!prototype) {
		return;
	}
	std::cout << "  견본 등록 : " << key << '\n';
	prototypes_[key] = std::move(prototype);
}

std::unique_ptr<RobotSpec> SpawnRegistry::spawn(const std::string& key,
                                                const std::string& namespaceName,
                                                double x, double y) const
{
	const auto it = prototypes_.find(key);
	if (it == prototypes_.end()) {
		std::cout << "  스폰 실패 : " << key << " 라는 견본이 없습니다\n";
		return nullptr;
	}
	std::unique_ptr<RobotSpec> fresh = it->second->clone();
	fresh->placeAt(namespaceName, x, y);
	return fresh;
}

void SpawnRegistry::listPrototypes() const
{
	for (const auto& [key, proto] : prototypes_) {
		std::cout << "  " << key << " -> ";
		proto->describe();
	}
}
