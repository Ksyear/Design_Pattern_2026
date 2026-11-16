#ifndef COMMAND_COMMAND_H
#define COMMAND_COMMAND_H

#include <string>

// Command - "무엇을 할지" 를 객체 하나에 담는다.
//
// 담기는 것은 세 가지다 : 받는 쪽(Receiver) + 할 일 + 필요한 값.
// 이렇게 묶어 두면 호출하는 쪽은 그것이 무슨 일인지 몰라도 된다.
//
// 로봇에서의 자리
//   ROS 2 액션(action)의 goal 이 바로 이 객체다. 네트워크로 보낼 수 있게
//   직렬화된 명령이고, 받은 쪽이 실행하고, 취소(cancel)할 수 있다.
//   MoveIt 의 플래닝 요청, 텔레옵 키 입력 하나하나도 같은 모양이다.
class Command {
public:
	virtual ~Command() = default;

	virtual void execute() = 0;
	virtual void undo() = 0;   // 로봇에서는 "반대로 움직이기" 가 된다
	virtual std::string name() const = 0;
};

#endif
