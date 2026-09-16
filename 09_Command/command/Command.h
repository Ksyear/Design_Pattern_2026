#ifndef COMMAND_COMMAND_H
#define COMMAND_COMMAND_H

// Command 인터페이스
//
// 핵심: 요청(무엇을, 누구에게)을 객체로 캡슐화한다.
//       인보커(리모컨)는 execute() 만 알고, 리시버(조명/선풍기)가 누구인지 모른다.
//       -> 요청을 저장/큐잉/로깅/취소할 수 있게 된다.
class Command {
public:
	virtual ~Command() = default;
	virtual void execute() = 0;
	virtual void undo() = 0;
};

#endif
