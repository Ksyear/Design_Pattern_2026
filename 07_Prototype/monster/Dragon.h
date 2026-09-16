#ifndef MONSTER_DRAGON_H
#define MONSTER_DRAGON_H

#include <memory>

#include "monster/Monster.h"

// Concrete Prototype : 자기 자신을 복사할 줄 아는 몬스터
class Dragon : public Monster {
public:
	Dragon();
	std::unique_ptr<Monster> clone() const override;
	void describe() const override;
};

#endif
