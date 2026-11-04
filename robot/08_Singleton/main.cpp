// 싱글턴 패턴 (Singleton) - 비상 정지 래치
//
// 책의 초콜릿 보일러(../../08_Singleton)와 같은 패턴이다.
//   ChocolateBoiler -> EmergencyStopBus
// 보일러가 둘이면 끓지 않은 우유를 붓고, e-stop 이 둘이면 팔이 계속 움직인다.
//
// C++ 의 이점 : 함수 지역 static 한 줄이면 끝이다.
//   자바의 DCL / volatile / enum 싱글턴 논쟁이 여기서는 필요 없다 (C++11 이후).
//
// 다만 로봇에서 이 패턴은 조심해서 써야 한다. 자세한 이유는 estop/EmergencyStopBus.h 주석에.
//   핵심만 : "프로세스 안에서 하나" 일 뿐이라, 노드를 프로세스로 나누는 순간 깨진다.
//
// 폴더 지도
//   estop/  싱글턴 본체 - EmergencyStopBus.*
//   node/   그것을 쓰는 서로 다른 노드 2개
#include <iostream>

#include "estop/EmergencyStopBus.h"
#include "node/ArmNode.h"
#include "node/NavigationNode.h"

int main()
{
	const NavigationNode nav;
	const ArmNode arm;

	std::cout << "===== 1. 정상 동작 =====\n";
	nav.publishCmdVel(0.4);
	arm.sendTrajectory("home");

	std::cout << "\n===== 2. 어디서 꺼내든 같은 객체인지 확인 =====\n";
	const EmergencyStopBus& a = EmergencyStopBus::instance();
	const EmergencyStopBus& b = EmergencyStopBus::instance();
	std::cout << "  instance() 두 번 호출 -> 같은 주소인가 : "
	          << ((&a == &b) ? "예" : "아니오") << '\n';

	std::cout << "\n===== 3. 안전 펜스 침입 - 한 곳에서 래치를 건다 =====\n";
	EmergencyStopBus::instance().trigger("안전 펜스 라이트커튼 차단");

	std::cout << "  서로 모르는 두 노드가 동시에 멈춘다 :\n";
	nav.publishCmdVel(0.4);
	arm.sendTrajectory("pick");

	std::cout << "\n===== 4. 사람이 버튼을 풀기 전까지는 계속 막힌다 =====\n";
	nav.publishCmdVel(0.1);

	std::cout << "\n===== 5. 해제 후 재개 =====\n";
	EmergencyStopBus::instance().reset();
	nav.publishCmdVel(0.4);
	arm.sendTrajectory("pick");

	std::cout << "\n  지금까지 래치가 걸린 횟수 : "
	          << EmergencyStopBus::instance().triggerCount() << "회\n";

	// 생각해 볼 것 :
	//   이 프로그램을 노드별로 두 프로세스로 나누면 어떻게 될까?
	//   -> 싱글턴이 프로세스마다 하나씩 생겨서 e-stop 이 한쪽에만 걸린다.
	//      그래서 실제 ROS 2 에서는 래치를 latched 토픽이나 서비스로 공유한다.
	//      싱글턴은 "한 프로세스 안" 이라는 전제가 있을 때만 맞는 답이다.
	return 0;
}
