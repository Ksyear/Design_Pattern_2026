#ifndef PERSON_PERSON_IMPL_H
#define PERSON_PERSON_IMPL_H

#include <string>

#include "person/Person.h"

// RealSubject : 권한 검사를 전혀 모른다. 그 일은 프록시가 한다.
class PersonImpl : public Person {
public:
	explicit PersonImpl(std::string name);

	std::string getName() const override;
	int getHotOrNotRating() const override;
	void setHotOrNotRating(int rating) override;
	void setInterests(const std::string& interests) override;

private:
	std::string name_;
	std::string interests_;
	int ratingSum_ = 0;
	int ratingCount_ = 0;
};

#endif
