#ifndef ESTOP_EMERGENCYSTOPBUS_H
#define ESTOP_EMERGENCYSTOPBUS_H

#include <string>

// 싱글턴 - 비상 정지 래치.
//
// 왜 하필 이것이 싱글턴인가
//   비상 정지는 하드웨어에 물리적으로 하나뿐인 회로다. 두 개일 수가 없다.
//   "버튼이 눌렸다" 는 사실을 프로세스 안의 모든 노드가 똑같이 봐야 하고,
//   누가 먼저 물어보든 같은 답이 나와야 한다.
//   객체가 둘이 되면 "내비게이션은 멈췄는데 팔은 계속 움직이는" 상태가 생긴다.
//
// C++ 에서의 구현 : 함수 지역 static 하나면 끝이다 (Meyers 싱글턴).
//   - C++11 부터 지역 static 초기화는 스레드 안전이 보장된다
//     -> 자바의 DCL(이중 검사 잠금)이나 volatile 이 필요 없다
//   - 복사와 이동을 지워야 실수로 사본이 생기지 않는다
//
// 주의 : 싱글턴은 대가가 크다. 실제 ROS 2 에서 쓰기 전에 생각해야 할 것들
//   1. 테스트 격리가 깨진다. 앞 테스트에서 건 e-stop 이 다음 테스트에 남는다
//      (그래서 아래에 reset() 을 열어 뒀다 - 테스트를 위해 필요한 구멍이다)
//   2. 컴포지션으로 여러 노드를 한 프로세스에 올리면 그 노드들이 상태를 공유한다.
//      반대로 프로세스를 나누면 싱글턴은 프로세스마다 따로 생긴다
//      -> "전역 하나" 라는 보장이 프로세스 경계에서 끊긴다. 로봇에서 특히 위험하다.
//   3. 상태를 바꾸는 부분(trigger/reset)은 여전히 스레드 안전하지 않다.
//      멀티스레드 실행기를 쓴다면 뮤텍스나 atomic 이 필요하다.
// 진짜 분산 시스템에서는 래치 상태를 토픽이나 서비스로 공유하는 쪽이 정석이다.
class EmergencyStopBus {
public:
	static EmergencyStopBus& instance();

	EmergencyStopBus(const EmergencyStopBus&) = delete;
	EmergencyStopBus& operator=(const EmergencyStopBus&) = delete;
	EmergencyStopBus(EmergencyStopBus&&) = delete;
	EmergencyStopBus& operator=(EmergencyStopBus&&) = delete;

	void trigger(const std::string& reason);
	void reset();  // 사람이 버튼을 풀어야만 풀린다

	bool isLatched() const;
	const std::string& reason() const;
	int triggerCount() const;

private:
	EmergencyStopBus() = default;
	~EmergencyStopBus() = default;

	bool latched_ = false;
	std::string reason_ = "(정상)";
	int triggerCount_ = 0;
};

#endif
