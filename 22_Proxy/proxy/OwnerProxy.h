#ifndef PROXY_OWNER_PROXY_H
#define PROXY_OWNER_PROXY_H

#include <memory>
#include <string>

#include "person/Person.h"

// 보호(protection) 프록시 - 본인용 프록시 : 자기 정보는 고칠 수 있지만 자기한테 점수는 못 준다
class OwnerProxy : public Person {
public:
	explicit OwnerProxy(std::shared_ptr<Person> p);

	std::string getName() const override;
	int getHotOrNotRating() const override;
	void setHotOrNotRating(int rating) override;
	void setInterests(const std::string& interests) override;

private:
	std::shared_ptr<Person> person_;
};

#endif
