#include "handler/SpamHandler.h"

#include <iostream>
#include <string>

bool SpamHandler::canHandle(const Email& m) const {
	return m.subject.find("[광고]") != std::string::npos;
}

void SpamHandler::process(const Email& m) const {
	std::cout << "  [스팸] 삭제: " << m.subject << '\n';
}
