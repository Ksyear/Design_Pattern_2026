#ifndef INGREDIENT_CLAMS_H
#define INGREDIENT_CLAMS_H

#include <string>

// Abstract Product : 조개. 어느 지역 조개인지는 여기서 알 바가 아니다.
class Clams {
public:
	virtual ~Clams() = default;
	virtual std::string name() const = 0;
};

#endif
