#include "handler/ComplaintHandler.h"

#include <iostream>
#include <string>

bool ComplaintHandler::canHandle(const Email& m) const {
	return m.body.find("항의") != std::string::npos || m.body.find("중독") != std::string::npos;
}

void ComplaintHandler::process(const Email& m) const {
	std::cout << "  [항의] 법무팀으로 전달: " << m.subject << '\n';
}
