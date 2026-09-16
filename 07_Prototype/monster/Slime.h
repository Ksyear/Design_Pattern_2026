#ifndef MONSTER_SLIME_H
#define MONSTER_SLIME_H

#include <memory>

#include "monster/Monster.h"

// Concrete Prototype : 자기 자신을 복사할 줄 아는 몬스터
class Slime : public Monster {
public:
	Slime();
	std::unique_ptr<Monster> clone() const override;
	void describe() const override;
};

#endif
