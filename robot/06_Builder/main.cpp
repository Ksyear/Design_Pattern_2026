// 빌더 패턴 (Builder) - 내비게이션 임무 조립
//
// 책의 휴가 계획표(../../06_Builder)와 같은 패턴이다.
//   VacationBuilder -> MissionBuilder
//   Director        -> MissionDirector
//   Vacation        -> Mission
//
// 로봇에서의 자리
//   nav2 의 웨이포인트 따라가기(FollowWaypoints) 액션에 넘길 목표 묶음,
//   비헤이비어 트리 XML, 런치 파일의 파라미터 묶음이 전부 이 모양으로 만들어진다.
//   조각이 많고, 조건에 따라 붙었다 말았다 하고, 다 모이기 전에는 쓰면 안 되는 것.
//
// 폴더 지도
//   mission/   Product  - Mission.* 과 Waypoint 구조체
//   builder/   Builder  - MissionBuilder.* (한 조각씩 쌓고 검증한다)
//   director/  Director - 자주 쓰는 조립 순서 두 가지
#include <iostream>
#include <stdexcept>

#include "builder/MissionBuilder.h"
#include "director/MissionDirector.h"

int main()
{
	std::cout << "===== 1. 디렉터가 만들어 주는 표준 임무 =====\n";
	MissionDirector::nightPatrol("patrol-01").print();

	std::cout << "\n===== 2. 같은 빌더로 만든 다른 임무 =====\n";
	MissionDirector::packageDelivery("deliver-03", 9.5, 4.0).print();

	std::cout << "\n===== 3. 조건에 따라 조각을 붙이기 =====\n";
	// 빌더가 진짜 힘을 쓰는 자리. 생성자 인자로는 이렇게 못 짠다.
	const bool batteryLow = true;
	const bool needInspection = false;

	MissionBuilder builder("adhoc-09");
	builder.waypoint("출발", 0.0, 0.0).waypoint("A동", 6.0, 3.0);
	if (needInspection) {
		builder.waypoint("검수대", 6.0, 6.0);
	}
	if (batteryLow) {
		builder.waypoint("충전도크", 0.0, 0.0).speedLimit(0.25);
	}
	builder.recovery("clear_costmap").build().print();

	std::cout << "\n===== 4. 덜 만들어진 임무는 태어나지도 못한다 =====\n";
	try {
		MissionBuilder("broken-00").speedLimit(1.0).build();
	} catch (const std::invalid_argument& e) {
		std::cout << "  build() 거부 : " << e.what() << '\n';
	}

	// 확인할 것 :
	//   Mission 에는 세터가 없다. 태어난 순간 이미 완전하고, 이후로 바뀌지 않는다.
	//   검증은 build() 한 곳에만 있다 -> 임무를 만드는 모든 경로가 같은 검사를 거친다.
	return 0;
}
