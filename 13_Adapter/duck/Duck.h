#ifndef DUCK_DUCK_H
#define DUCK_DUCK_H

// Target : 클라이언트가 기대하는 인터페이스
class Duck {
public:
	virtual ~Duck() = default;
	virtual void quack() const = 0;
	virtual void fly() const = 0;
};

#endif
