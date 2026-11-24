// 퍼사드 패턴 (Facade) - 자율주행 시동 절차
//
// 책의 홈시어터(../../14_Facade)와 같은 패턴이다.
//   HomeTheaterFacade -> AutonomyFacade
//   watchMovie()      -> startAutonomy()
//   endMovie()        -> shutdown()
//
// 로봇에서의 자리
//   실제 로봇을 켜는 일은 런치 파일 하나로 끝나지 않는다.
//   전원, 모터 드라이버, 브레이크, 센서 스핀업, 측위 수렴, 라이프사이클 전이까지
//   순서가 정해져 있고 틀리면 위험하다. ros2 launch 의 런치 파일과
//   nav2_lifecycle_manager 가 실제로 이 파사드 역할을 한다.
//
// 원칙 : 최소 지식 원칙(디미터 법칙)
//   호출하는 쪽이 다섯 개 장치를 다 알 필요가 없다. 친구 하나만 알면 된다.
//
// 폴더 지도
//   subsystem/  하위 시스템 5개 - 서로를 전혀 모른다
//   facade/     AutonomyFacade.* - 순서를 아는 유일한 곳
#include <iostream>

#include "facade/AutonomyFacade.h"

int main()
{
	AutonomyFacade robot;

	std::cout << "===== 1. 파사드 없이 직접 한다면 =====\n";
	std::cout << "  호출하는 쪽이 이 순서를 전부 알아야 한다 :\n";
	std::cout << "    power.enable24V(); motors.enable(); motors.releaseBrake();\n";
	std::cout << "    lidar.spinUp(); amcl.loadMap(); amcl.setInitialPose();\n";
	std::cout << "    amcl.waitForConvergence(); nav.configure(); nav.activate();\n";
	std::cout << "  -> 순서를 아는 곳이 여러 군데가 되고, 언젠가 한 곳이 틀린다\n\n";

	std::cout << "===== 2. 파사드로 한 줄 =====\n";
	if (!robot.startAutonomy("warehouse_1f.yaml", 0.0, 0.0)) {
		return 1;  // 시동 실패를 무시하고 다음 장면으로 가지 않는다
	}

	std::cout << "\n===== 3. 정비 모드 - 파사드는 막지 않는다 =====\n";
	// 파사드는 편의를 제공할 뿐 하위 시스템을 봉인하지 않는다.
	// 캘리브레이션처럼 절차를 벗어난 작업은 직접 접근해야 한다.
	std::cout << "  브레이크만 따로 체결 (정비용) :\n";
	robot.motors().engageBrake();

	std::cout << "\n===== 4. 종료 - 역순도 파사드가 안다 =====\n";
	robot.shutdown();

	std::cout << "\n===== 5. 측위 실패 - 켠 것만 되돌린다 =====\n";
	if (!robot.startAutonomy("missing_map.yaml", 0.0, 0.0)) {
		std::cout << "  -> 시동 거부. nav2 는 configure 전이라 deactivate 를 보내지 않았다\n";
	}

	// 확인할 것 :
	//   subsystem/ 의 다섯 파일은 서로를 모른다. 파사드만 다섯을 다 안다.
	//   파사드를 쓴다고 하위 시스템 기능이 줄지 않는다 (3번 장면).
	//   실패하면 이미 켠 것만 역순으로 되돌린다 (5번 장면).
	//   어댑터와의 차이 : 어댑터는 형식을 바꾸고, 파사드는 쓰기 쉽게 만든다.
	return 0;
}
