// 커맨드 패턴 (Command) - 텔레옵 콘솔과 로봇 명령
//
// 책의 IoT 리모컨(../../09_Command)과 같은 패턴이다.
//   RemoteControl -> TeleopConsole   (Invoker - 버튼만 누른다)
//   Light / Stereo -> MobileBase / Gripper  (Receiver - 실제로 일한다)
//   LightOnCommand -> MoveCommand 등  (Command - 무엇을 할지 담은 객체)
//   MacroCommand   -> MacroCommand    (여러 개를 하나처럼)
//
// 로봇에서의 자리
//   ROS 2 액션의 goal 이 곧 명령 객체다. 보낼 수 있고, 큐에 쌓을 수 있고,
//   취소할 수 있고, 로그로 남길 수 있다 - 함수 호출로는 못 하는 일들이다.
//   "명령을 객체로 만든다" 는 것이 분산 로봇 시스템의 전제 조건인 셈이다.
//
// 폴더 지도
//   device/   Receiver - MobileBase / Gripper (실제 장치)
//   command/  Command  - Command.h(인터페이스) + 구상 명령 5개
//   console/  Invoker  - TeleopConsole.* (슬롯과 되돌리기 기록)
#include <iostream>
#include <memory>
#include <vector>

#include "command/GripCommand.h"
#include "command/MacroCommand.h"
#include "command/MoveCommand.h"
#include "command/NoCommand.h"
#include "command/TurnCommand.h"
#include "console/TeleopConsole.h"
#include "device/Gripper.h"
#include "device/MobileBase.h"

int main()
{
	MobileBase base;
	Gripper gripper;
	TeleopConsole console;

	std::cout << "===== 1. 버튼에 명령 꽂기 =====\n";
	console.assign(0, std::make_unique<MoveCommand>(&base, 1.0));
	console.assign(1, std::make_unique<TurnCommand>(&base, 90.0));
	console.assign(2, std::make_unique<GripCommand>(&gripper, true));
	console.printSlots();

	std::cout << "\n===== 2. 눌러 보기 =====\n";
	console.press(0);
	console.press(1);
	console.press(0);
	base.report();

	std::cout << "\n===== 3. 되돌리기 - 마지막 동작을 반대로 =====\n";
	console.undoLast();
	base.report();

	std::cout << "\n===== 4. 빈 슬롯을 눌러도 아무 일도 안 난다 (널 객체) =====\n";
	console.press(3);

	std::cout << "\n===== 5. 매크로 - 집품 시퀀스를 버튼 하나에 =====\n";
	std::vector<std::unique_ptr<Command>> steps;
	steps.push_back(std::make_unique<MoveCommand>(&base, 0.5));
	steps.push_back(std::make_unique<GripCommand>(&gripper, true));
	steps.push_back(std::make_unique<TurnCommand>(&base, 180.0));
	console.assign(3, std::make_unique<MacroCommand>("집품", std::move(steps)));
	console.printSlots();
	console.press(3);
	base.report();

	std::cout << "\n===== 6. 매크로 되돌리기 - 역순이어야 하는 이유 =====\n";
	// 앞에서부터 되돌리면 물건을 쥔 채로 후진하게 된다.
	console.undoLast();
	base.report();

	// 확인할 것 :
	//   TeleopConsole.cpp 안에 MobileBase / Gripper 라는 이름이 없다.
	//   장치를 추가해도 콘솔은 그대로고, 새 명령 클래스 하나만 늘어난다.
	//   명령이 객체이기 때문에 기록(history_)에 쌓을 수 있었다
	//   -> 그 기록을 파일로 저장하면 그대로 재생 가능한 작업 스크립트가 된다.
	return 0;
}
