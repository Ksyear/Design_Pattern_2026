#ifndef NODE_ARMNODE_H
#define NODE_ARMNODE_H

// 로봇 팔 노드. 내비게이션과 완전히 다른 코드인데 같은 래치를 본다.
class ArmNode {
public:
	void sendTrajectory(const char* poseName) const;
};

#endif
