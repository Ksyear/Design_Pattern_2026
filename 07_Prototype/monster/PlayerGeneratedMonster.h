#ifndef MONSTER_PLAYER_GENERATED_MONSTER_H
#define MONSTER_PLAYER_GENERATED_MONSTER_H

#include <memory>
#include <string>
#include <vector>

#include "monster/Monster.h"

// 헤비 유저가 직접 만든 몬스터.
// 클래스를 새로 짜지 않고 '설정이 다른 프로토타입'으로 등록한다.
class PlayerGeneratedMonster : public Monster {
public:
	PlayerGeneratedMonster(std::string name, int hp, std::vector<std::string> skills);
	std::unique_ptr<Monster> clone() const override;
	void describe() const override;
};

#endif
