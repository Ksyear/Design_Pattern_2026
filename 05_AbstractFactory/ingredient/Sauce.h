#ifndef INGREDIENT_SAUCE_H
#define INGREDIENT_SAUCE_H

#include <string>

// Abstract Product : 소스. 어느 지역 소스인지는 여기서 알 바가 아니다.
class Sauce {
public:
	virtual ~Sauce() = default;
	virtual std::string name() const = 0;
};

#endif
