#ifndef INGREDIENT_CHEESE_H
#define INGREDIENT_CHEESE_H

#include <string>

// Abstract Product : 치즈. 어느 지역 치즈인지는 여기서 알 바가 아니다.
class Cheese {
public:
	virtual ~Cheese() = default;
	virtual std::string name() const = 0;
};

#endif
