#ifndef MONSTER_MONSTER_H
#define MONSTER_MONSTER_H

#include <memory>
#include <string>
#include <vector>

// Prototype 인터페이스
//
// 핵심: "어떤 클래스인지 모르는 채로" 복사만으로 새 인스턴스를 만든다.
//       clone() 은 자기 클래스를 아는 객체 자신이 구현하므로 private 필드까지 온전히 복사된다.
//
// C++ 주의
//   - 복사 생성자만으로는 부족하다. 기반 클래스 포인터로 들고 있으면 슬라이싱이 나므로
//     가상 clone() 이 반드시 필요하다.
//   - 얕은 복사(shallow) vs 깊은 복사(deep)를 의식적으로 골라야 한다.
//
// 필드는 private, 읽기는 protected 접근자로. 서브클래스는 describe() 에서 읽기만 하고
// 값을 쓰는 통로는 생성자와 공개 세터 둘뿐이다.
class Monster {
public:
	virtual ~Monster() = default;
	virtual std::unique_ptr<Monster> clone() const = 0;   // <-- 가상 복사 생성자
	virtual void describe() const = 0;

	void setName(std::string n);
	void addSkill(std::string s);

protected:
	Monster(std::string name, int hp, std::vector<std::string> skills);

	const std::string& name() const;
	int hp() const;
	const std::vector<std::string>& skills() const;

private:
	std::string name_;
	int hp_;
	std::vector<std::string> skills_;
};

#endif
