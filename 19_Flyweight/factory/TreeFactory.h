#ifndef FACTORY_TREE_FACTORY_H
#define FACTORY_TREE_FACTORY_H

#include <cstddef>
#include <memory>
#include <string>
#include <unordered_map>

#include "flyweight/TreeType.h"

// Flyweight Factory : 풀을 관리하고 재사용을 보장한다.
// 클라이언트가 직접 TreeType 을 만들지 못하게 하는 것이 이 클래스의 존재 이유다.
class TreeFactory {
public:
	const TreeType& getTreeType(const std::string& name, const std::string& color,
	                            const std::string& texture);

	std::size_t poolSize() const;

private:
	std::unordered_map<std::string, std::unique_ptr<TreeType>> pool_;
};

#endif
