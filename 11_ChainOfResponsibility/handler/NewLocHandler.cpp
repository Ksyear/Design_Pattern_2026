#include "handler/NewLocHandler.h"

#include <iostream>
#include <string>

bool NewLocHandler::canHandle(const Email& m) const {
	return m.body.find("설치") != std::string::npos;
}

void NewLocHandler::process(const Email& m) const {
	std::cout << "  [신규 설치 요청] 영업부로 전달: " << m.subject << '\n';
}
