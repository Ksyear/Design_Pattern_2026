#include "save/CheckpointStack.h"

#include <iostream>
#include <stdexcept>

void CheckpointStack::push(const Navigator::Snapshot& snapshot)
{
	std::cout << "    체크포인트 저장 : " << snapshot.label() << '\n';
	stack_.push_back(snapshot);
}

bool CheckpointStack::empty() const
{
	return stack_.empty();
}

Navigator::Snapshot CheckpointStack::pop()
{
	if (stack_.empty()) {
		throw std::out_of_range("보관된 체크포인트가 없습니다");
	}
	Navigator::Snapshot top = stack_.back();
	stack_.pop_back();
	return top;
}

void CheckpointStack::list() const
{
	std::cout << "  보관 중인 체크포인트 :";
	for (const Navigator::Snapshot& s : stack_) {
		std::cout << " [" << s.label() << ']';
	}
	std::cout << '\n';
}
