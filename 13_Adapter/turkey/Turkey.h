#ifndef TURKEY_TURKEY_H
#define TURKEY_TURKEY_H

// Adaptee : 인터페이스가 안 맞는 기존 클래스
class Turkey {
public:
	virtual ~Turkey() = default;
	virtual void gobble() const = 0;
	virtual void fly() const = 0;   // 칠면조는 짧게만 난다
};

#endif
