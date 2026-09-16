#include "proxy/LoggingImageProxy.h"

#include <iostream>
#include <utility>

LoggingImageProxy::LoggingImageProxy(std::unique_ptr<Image> inner) : inner_(std::move(inner)) {}

void LoggingImageProxy::display() const {
	std::cout << "  [로그] display() 호출 #" << ++calls_ << '\n';
	inner_->display();
}
