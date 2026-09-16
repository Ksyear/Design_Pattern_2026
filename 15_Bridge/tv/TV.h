#ifndef TV_T_V_H
#define TV_T_V_H

#include <string>

// Implementation : 저수준, 실제 일을 한다.
//
// 주의: 브리지에서 말하는 '추상화/구현'은 C++ 의 abstract class 가 아니라
//       '고수준 제어 계층 / 저수준 실행 계층'이라는 아키텍처 용어다.
class TV {
public:
	virtual ~TV() = default;
	virtual void on() = 0;
	virtual void off() = 0;
	virtual void tuneChannel(int channel) = 0;
	virtual std::string brand() const = 0;
};

#endif
