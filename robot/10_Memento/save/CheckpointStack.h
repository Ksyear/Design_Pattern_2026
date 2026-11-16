#ifndef SAVE_CHECKPOINTSTACK_H
#define SAVE_CHECKPOINTSTACK_H

#include <vector>

#include "nav/Navigator.h"

// Caretaker - 스냅샷을 보관만 한다.
//
// 이 클래스는 스냅샷 안에 좌표가 들어 있는지 배터리가 들어 있는지 모른다.
// label() 말고는 볼 수 있는 것이 없다. 그것이 메멘토 패턴의 요점이다
// (상태를 밖으로 빼되, 캡슐화는 깨지 않는다).
class CheckpointStack {
public:
	void push(const Navigator::Snapshot& snapshot);
	bool empty() const;

	// 마지막 체크포인트를 꺼낸다. 비어 있으면 호출하면 안 된다.
	Navigator::Snapshot pop();

	void list() const;

private:
	std::vector<Navigator::Snapshot> stack_;
};

#endif
