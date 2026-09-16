#include "boiler/ChocolateBoiler.h"

#include <iostream>

ChocolateBoiler& ChocolateBoiler::getInstance() {
	static ChocolateBoiler instance;   // <-- Meyers Singleton
	return instance;
}

ChocolateBoiler::ChocolateBoiler() : empty_(true), boiled_(false) {
	std::cout << "[보일러 생성] 딱 한 번만 찍혀야 정상\n";
}

void ChocolateBoiler::fill() {
	std::lock_guard<std::mutex> lock(mutex_);
	if (isEmpty()) {
		empty_ = false;
		boiled_ = false;
		std::cout << "  보일러에 우유와 초콜릿을 채웠습니다\n";
	} else {
		std::cout << "  이미 차 있습니다 (넘치지 않게 막음)\n";
	}
}

void ChocolateBoiler::boil() {
	std::lock_guard<std::mutex> lock(mutex_);
	if (!isEmpty() && !isBoiled()) {
		boiled_ = true;
		std::cout << "  내용물을 끓입니다\n";
	}
}

void ChocolateBoiler::drain() {
	std::lock_guard<std::mutex> lock(mutex_);
	if (!isEmpty() && isBoiled()) {
		empty_ = true;
		std::cout << "  끓인 재료를 다음 단계로 넘겼습니다\n";
	}
}

bool ChocolateBoiler::isEmpty() const {
	return empty_;
}

bool ChocolateBoiler::isBoiled() const {
	return boiled_;
}
