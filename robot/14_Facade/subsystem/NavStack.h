#ifndef SUBSYSTEM_NAVSTACK_H
#define SUBSYSTEM_NAVSTACK_H

// 내비게이션 스택 - 라이프사이클 노드들을 configure -> activate 순으로 올리고,
// deactivate -> cleanup 순으로 내린다 (cleanup 까지 해야 다시 configure 할 수 있다)
class NavStack {
public:
	void configure();
	void activate();
	void deactivate();
	void cleanup();
};

#endif
