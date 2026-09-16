#ifndef PERSON_PERSON_H
#define PERSON_PERSON_H

#include <string>

// 보호 프록시가 감쌀 Subject
class Person {
public:
	virtual ~Person() = default;
	virtual std::string getName() const = 0;
	virtual int getHotOrNotRating() const = 0;
	virtual void setHotOrNotRating(int rating) = 0;
	virtual void setInterests(const std::string& interests) = 0;
};

#endif
