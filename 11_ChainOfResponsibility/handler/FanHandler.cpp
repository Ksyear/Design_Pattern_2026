#include "handler/FanHandler.h"

#include <iostream>
#include <string>

bool FanHandler::canHandle(const Email& m) const {
	return m.body.find("최고") != std::string::npos || m.body.find("감사") != std::string::npos;
}

void FanHandler::process(const Email& m) const {
	std::cout << "  [팬 메일] CEO에게 전달: " << m.subject << '\n';
}
