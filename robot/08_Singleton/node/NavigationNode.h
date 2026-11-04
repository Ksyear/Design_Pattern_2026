#ifndef NODE_NAVIGATIONNODE_H
#define NODE_NAVIGATIONNODE_H

// 이동을 담당하는 노드. 속도를 내보내기 전에 래치를 확인한다.
class NavigationNode {
public:
	void publishCmdVel(double linearX) const;
};

#endif
