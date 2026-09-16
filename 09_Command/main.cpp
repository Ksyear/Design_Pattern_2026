// 커맨드 패턴 (Command) - 헤드 퍼스트 6장 만능 IoT 리모컨
//
// 이 파일은 Client 역할이다. 리시버 -> 커맨드 -> 인보커 순으로 조립만 한다.
//   device/   Receiver - Light.*, CeilingFan.*  (실제로 일하는 장치)
//   command/  요청      - Command.h + 구상 커맨드 + NoCommand + MacroCommand
//   remote/   Invoker  - RemoteControl.*
//
// remote/ 는 device/ 를 전혀 모른다. 둘을 이어 붙이는 일은 오직 이 파일이 한다.
#include <iostream>

#include "command/CeilingFanCommand.h"
#include "command/LightOffCommand.h"
#include "command/LightOnCommand.h"
#include "command/MacroCommand.h"
#include "device/CeilingFan.h"
#include "device/Light.h"
#include "remote/RemoteControl.h"

int main() {
	// Client : 리시버 -> 커맨드 -> 인보커 순으로 조립한다
	Light livingRoomLight("거실");
	Light kitchenLight("주방");
	CeilingFan fan("거실");

	LightOnCommand livingRoomOn(livingRoomLight);
	LightOffCommand livingRoomOff(livingRoomLight);
	LightOnCommand kitchenOn(kitchenLight);
	LightOffCommand kitchenOff(kitchenLight);
	CeilingFanCommand fanHigh(fan, CeilingFan::High);
	CeilingFanCommand fanMedium(fan, CeilingFan::Medium);
	CeilingFanCommand fanOff(fan, CeilingFan::Off);

	RemoteControl remote;
	remote.setCommand(0, &livingRoomOn, &livingRoomOff);
	remote.setCommand(1, &kitchenOn, &kitchenOff);
	remote.setCommand(2, &fanHigh, &fanOff);

	std::cout << "--- 기본 동작과 작업 취소 ---\n";
	remote.onButtonWasPushed(0);
	remote.offButtonWasPushed(0);
	remote.undoButtonWasPushed();

	std::cout << "\n--- 상태가 있는 작업 취소 (선풍기) ---\n";
	remote.setCommand(2, &fanMedium, &fanOff);
	remote.onButtonWasPushed(2);            // 꺼짐 -> 중
	remote.setCommand(2, &fanHigh, &fanOff);
	remote.onButtonWasPushed(2);            // 중 -> 강
	remote.undoButtonWasPushed();           // 강 -> 중 (전역 Off가 아니라 '직전 상태')

	std::cout << "\n--- 매크로 커맨드 ---\n";
	MacroCommand partyOn({&livingRoomOn, &kitchenOn, &fanHigh});
	MacroCommand partyOff({&livingRoomOff, &kitchenOff, &fanOff});
	remote.setCommand(3, &partyOn, &partyOff);
	remote.onButtonWasPushed(3);
	remote.undoButtonWasPushed();

	return 0;
}
