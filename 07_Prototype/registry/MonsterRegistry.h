#ifndef REGISTRY_MONSTER_REGISTRY_H
#define REGISTRY_MONSTER_REGISTRY_H

#include <map>
#include <memory>
#include <string>

#include "monster/Monster.h"

// Prototype Registry
// 클라이언트는 문자열 키만 알고, 어떤 구상 클래스가 나오는지는 끝까지 모른다.
class MonsterRegistry {
public:
	void registerPrototype(const std::string& key, std::unique_ptr<Monster> proto);
	std::unique_ptr<Monster> create(const std::string& key) const;

private:
	std::map<std::string, std::unique_ptr<Monster>> prototypes_;
};

#endif
