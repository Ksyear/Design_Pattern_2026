#ifndef MENU_MENU_H
#define MENU_MENU_H

#include <memory>
#include <string>

#include "iterator/Iterator.h"

// 집합체(Aggregate) 인터페이스 : "나를 훑을 반복자를 하나 만들어 줘"
//
// 단일 역할 원칙: 컬렉션은 '항목 관리'만, 반복은 반복자 객체가 맡는다.
class Menu {
public:
	virtual ~Menu() = default;
	virtual std::unique_ptr<Iterator> createIterator() const = 0;
	virtual const std::string& title() const = 0;
};

#endif
