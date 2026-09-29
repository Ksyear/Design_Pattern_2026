#ifndef SUBJECT_PUBLISHER_H
#define SUBJECT_PUBLISHER_H

#include "observer/Subscriber.h"

class Publisher {
public:
	virtual ~Publisher() = default;

	virtual void subscribe(Subscriber* sub) = 0;
	virtual void unsubscribe(Subscriber* sub) = 0;
	virtual void notify() = 0;
};

#endif
