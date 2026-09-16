#ifndef MAIL_EMAIL_H
#define MAIL_EMAIL_H

#include <string>

// 사슬을 타고 흐르는 요청
struct Email {
	std::string from;
	std::string subject;
	std::string body;
};

#endif
