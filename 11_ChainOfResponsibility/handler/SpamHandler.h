#ifndef HANDLER_SPAM_HANDLER_H
#define HANDLER_SPAM_HANDLER_H

#include "handler/Handler.h"

// ConcreteHandler : 제목으로 거른다. 자기 다음이 누구인지는 모른다.
class SpamHandler : public Handler {
protected:
	bool canHandle(const Email& m) const override;
	void process(const Email& m) const override;
};

#endif
