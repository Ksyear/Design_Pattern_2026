#ifndef HANDLER_FAN_HANDLER_H
#define HANDLER_FAN_HANDLER_H

#include "handler/Handler.h"

// ConcreteHandler : 본문 키워드로 거른다. 자기 다음이 누구인지는 모른다.
class FanHandler : public Handler {
protected:
	bool canHandle(const Email& m) const override;
	void process(const Email& m) const override;
};

#endif
