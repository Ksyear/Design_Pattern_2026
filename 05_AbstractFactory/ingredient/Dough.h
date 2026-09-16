#ifndef INGREDIENT_DOUGH_H
#define INGREDIENT_DOUGH_H

#include <string>

// Abstract Product : 도우. 어느 지역 도우인지는 여기서 알 바가 아니다.
class Dough {
public:
	virtual ~Dough() = default;
	virtual std::string name() const = 0;
};

#endif
