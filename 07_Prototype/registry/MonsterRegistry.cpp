#include "registry/MonsterRegistry.h"

#include <utility>

void MonsterRegistry::registerPrototype(const std::string& key, std::unique_ptr<Monster> proto) {
	prototypes_[key] = std::move(proto);
}

std::unique_ptr<Monster> MonsterRegistry::create(const std::string& key) const {
	auto it = prototypes_.find(key);
	if (it == prototypes_.end()) return nullptr;
	return it->second->clone();
}
