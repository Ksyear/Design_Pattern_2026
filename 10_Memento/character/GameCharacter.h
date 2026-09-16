#ifndef CHARACTER_GAME_CHARACTER_H
#define CHARACTER_GAME_CHARACTER_H

#include <memory>
#include <string>

// Originator
//
// 핵심: 객체의 상태를 '캡슐화를 깨지 않고' 저장/복구한다.
//       - 오리지네이터(Originator)만 메멘토 속을 들여다볼 수 있다
//       - 케어테이커(Caretaker)는 메멘토를 보관만 하고 내용은 못 본다
//
// C++ 구현 요령
//   자바의 중첩 클래스 대신 '중첩 클래스 + private 생성자 + friend' 로 같은 효과를 낸다.
class GameCharacter {
public:
	// Memento : 밖에서는 이 타입을 '불투명한 토큰'으로만 다룰 수 있다
	class Memento {
	public:
		// 케어테이커에게 보여 줄 메타데이터만 공개
		const std::string& label() const { return label_; }

	private:
		friend class GameCharacter;   // <-- 속을 볼 수 있는 유일한 클래스

		Memento(int level, int hp, std::string weapon, std::string label);

		int level_;
		int hp_;
		std::string weapon_;
		std::string label_;
	};

	explicit GameCharacter(std::string name);

	void levelUp(const std::string& newWeapon);
	void takeDamage(int dmg);
	bool isDead() const;
	void show() const;

	// 스냅숏 생성 - 자기 상태를 자기가 포장한다
	std::unique_ptr<Memento> save(const std::string& label) const;

	// 스냅숏 복구 - 자기 상태를 자기가 되돌린다
	void restore(const Memento& m);

private:
	std::string name_;
	int level_ = 1;
	int hp_ = 120;
	std::string weapon_ = "나무 막대기";
};

#endif
