#include "handler/Handler.h"

#include <iostream>
#include <utility>

Handler* Handler::setNext(std::unique_ptr<Handler> next) {
	Handler* raw = next.get();
	next_ = std::move(next);
	return raw;
}

void Handler::handle(const Email& mail) {
	if (canHandle(mail)) {
		process(mail);
		return;
	}
	if (next_) {
		next_->handle(mail);
		return;
	}
	// 사슬 끝까지 갔는데 아무도 안 받았다 - CoR의 대표적인 단점
	std::cout << "  [미처리] 아무 핸들러도 받지 않음: " << mail.subject << '\n';
}
