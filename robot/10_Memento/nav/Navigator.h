#ifndef NAV_NAVIGATOR_H
#define NAV_NAVIGATOR_H

#include <string>

// Originator - 상태를 가진 쪽. 자기 상태를 스냅샷으로 떠 주고, 다시 받아 복원한다.
//
// 로봇에서의 자리
//   자율주행 중 로컬라이제이션이 튀거나(파티클 발산), 임무가 실패해서
//   "조금 전 상태" 로 돌아가야 할 때가 있다. 그때 필요한 것이 이것이다.
//   nav2 의 웨이포인트 재시도, AMCL 의 초기 위치 재설정이 같은 발상이다.
class Navigator {
public:
	// Memento - 중첩 클래스 + friend 가 C++ 에서 캡슐화를 지키는 방법이다.
	//
	//   - 멤버가 private 이라 Navigator 말고는 아무도 내용을 못 본다
	//   - friend 선언 덕분에 Navigator 만 만들고 읽을 수 있다
	//   - 보관하는 쪽(CheckpointStack)은 이 객체를 "들고만" 있을 수 있다
	// 자바의 내부 클래스 접근 규칙을 C++ 에서 재현한 것이다.
	class Snapshot {
	public:
		const std::string& label() const;  // 보관하는 쪽에 허락된 유일한 정보

	private:
		friend class Navigator;
		Snapshot(std::string label, double x, double y, double yaw, int waypointIndex, double battery);

		std::string label_;
		double x_;
		double y_;
		double yaw_;
		int waypointIndex_;
		double battery_;
	};

	Navigator(double x, double y, double yaw);

	void driveTo(double x, double y, double yaw, double batteryCost);
	void reachWaypoint();
	void report() const;

	Snapshot save(std::string label) const;
	void restore(const Snapshot& snapshot);

private:
	double x_;
	double y_;
	double yaw_;
	int waypointIndex_ = 0;
	double battery_ = 1.0;
};

#endif
