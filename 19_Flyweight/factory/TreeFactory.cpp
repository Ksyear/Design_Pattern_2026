#include "factory/TreeFactory.h"

#include <iostream>

const TreeType& TreeFactory::getTreeType(const std::string& name, const std::string& color,
                                         const std::string& texture) {
	const std::string key = name + '|' + color + '|' + texture;
	auto it = pool_.find(key);
	if (it == pool_.end()) {
		std::cout << "[신규 생성] " << key << '\n';
		it = pool_.emplace(key, std::make_unique<TreeType>(name, color, texture)).first;
	}
	return *it->second;
}

std::size_t TreeFactory::poolSize() const {
	return pool_.size();
}
