#ifndef HANDLER_HANDLER_H
#define HANDLER_HANDLER_H

#include <memory>

#include "mail/Email.h"

// Handler + BaseHandler
//
// 핵심: 요청을 검토하는 객체 사슬을 만든다.
//       각 핸들러는 (1) 내가 처리할지 (2) 다음에게 넘길지 두 가지만 결정한다.
//       -> 보낸 쪽은 누가 처리했는지 모른다. 사슬 구성만 바꾸면 역할이 바뀐다.
//
// 다음 핸들러를 들고 넘기는 공통 코드를 기반 클래스에 몰아넣었다.
class Handler {
public:
	virtual ~Handler() = default;

	// setNext 가 자기 인자를 그대로 돌려주므로 사슬을 체이닝으로 엮을 수 있다
	Handler* setNext(std::unique_ptr<Handler> next);

	void handle(const Email& mail);

protected:
	virtual bool canHandle(const Email& mail) const = 0;
	virtual void process(const Email& mail) const = 0;

private:
	std::unique_ptr<Handler> next_;
};

#endif
