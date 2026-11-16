// 메멘토 패턴 (Memento) - 자율주행 체크포인트와 복구
//
// 책의 RPG 세이브 슬롯(../../10_Memento)과 같은 패턴이다.
//   GameCharacter -> Navigator        (Originator)
//   Memento       -> Navigator::Snapshot
//   SaveSlot      -> CheckpointStack  (Caretaker)
//
// 로봇에서의 자리
//   긴 임무 중 로컬라이제이션이 발산하거나 경로 추종이 실패하면
//   "마지막으로 확실했던 지점" 으로 되돌려야 한다.
//   nav2 의 재시도, AMCL 초기 위치 재설정, 작업 셀의 공정 롤백이 전부 이 모양이다.
//
// C++ 의 핵심 : 중첩 클래스 + friend
//   보관하는 쪽은 스냅샷을 들고만 있을 뿐 내용을 못 본다.
//   자바의 내부 클래스 접근을 C++ 에서 재현한 것이다.
//
// 폴더 지도
//   nav/   Originator + 중첩 Memento - Navigator.*
//   save/  Caretaker               - CheckpointStack.*
#include <iostream>

#include "nav/Navigator.h"
#include "save/CheckpointStack.h"

int main()
{
	Navigator nav(0.0, 0.0, 0.0);
	CheckpointStack checkpoints;

	std::cout << "===== 1. 출발 =====\n";
	nav.report();

	std::cout << "\n===== 2. 첫 구간 주행 후 체크포인트 =====\n";
	nav.driveTo(5.0, 0.0, 0.0, 0.08);
	nav.reachWaypoint();
	checkpoints.push(nav.save("복도 진입"));
	nav.report();

	std::cout << "\n===== 3. 두 번째 구간 =====\n";
	nav.driveTo(5.0, 6.0, 90.0, 0.10);
	nav.reachWaypoint();
	checkpoints.push(nav.save("교차로"));
	nav.report();

	std::cout << "\n===== 4. 주행 중 로컬라이제이션 발산 =====\n";
	nav.driveTo(41.0, -3.0, 210.0, 0.05);  // 위치 추정이 튀었다
	std::cout << "  AMCL 파티클 발산 - 추정 위치가 지도 밖으로 튐\n";
	nav.report();

	std::cout << "\n===== 5. 마지막 확실한 지점으로 복구 =====\n";
	checkpoints.list();
	nav.restore(checkpoints.pop());
	nav.report();

	std::cout << "\n===== 6. 더 이전 지점으로도 갈 수 있다 =====\n";
	nav.restore(checkpoints.pop());
	nav.report();

	std::cout << "\n===== 7. 보관함이 비었을 때 =====\n";
	std::cout << "  비었는가 : " << (checkpoints.empty() ? "예" : "아니오") << '\n';

	// 확인할 것 :
	//   CheckpointStack.cpp 에서 스냅샷의 x, y 를 읽어 보려고 하면 컴파일이 안 된다.
	//   private 이고 friend 도 아니기 때문이다 -> 캡슐화가 지켜진 채로 상태만 오간다.
	//
	//   현실과 다른 점도 하나 : 복원은 "추정 상태" 만 되돌린다.
	//   로봇의 실제 물리 위치는 그대로다. 진짜 시스템에서는 복원 후
	//   센서로 위치를 다시 확인하는 단계가 반드시 따라붙는다.
	return 0;
}
