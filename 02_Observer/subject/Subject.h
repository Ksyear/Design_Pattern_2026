#ifndef SUBJECT_SUBJECT_H
#define SUBJECT_SUBJECT_H

#include <memory>

#include "observer/Observer.h"

// 주제 인터페이스 : 옵저버를 등록/해지/통보하는 계약만 선언한다
class Subject {
public:
	virtual ~Subject() = default;
	virtual void registerObserver(const std::shared_ptr<Observer>& o) = 0;
	virtual void removeObserver(const std::shared_ptr<Observer>& o) = 0;
	virtual void notifyObservers() = 0;
};

#endif
