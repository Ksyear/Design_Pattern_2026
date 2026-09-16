#ifndef PROXY_NON_OWNER_PROXY_H
#define PROXY_NON_OWNER_PROXY_H

#include <memory>
#include <string>

#include "person/Person.h"

// 보호(protection) 프록시 - 타인용 프록시 : 점수는 줄 수 있지만 남의 정보는 못 고친다
class NonOwnerProxy : public Person {
public:
	explicit NonOwnerProxy(std::shared_ptr<Person> p);

	std::string getName() const override;
	int getHotOrNotRating() const override;
	void setHotOrNotRating(int rating) override;
	void setInterests(const std::string& interests) override;

private:
	std::shared_ptr<Person> person_;
};

#endif
