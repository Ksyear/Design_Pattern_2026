// [연습] 커맨드 패턴 - 다중 실행 취소(undo 스택)와 작업 큐
//
// main.cpp의 리모컨은 undo가 '한 단계'뿐이다. 실전에서는 부족하다.
//
// TODO 1. RemoteControl에 std::vector<Command*> undoStack_ 을 두고
//         버튼을 누를 때마다 push, undo를 누르면 pop 하도록 고칠 것
// TODO 2. redoStack_ 을 추가해 '다시 실행'까지 지원할 것
//         (주의: 새 명령을 실행하면 redo 스택은 비워야 한다)
// TODO 3. Command를 큐에 쌓아 두고 나중에 한꺼번에 실행하는 JobQueue를 만들 것
//         -> 커맨드 패턴이 "요청을 큐에 저장"할 수 있다는 정의를 코드로 확인
// TODO 4. 각 Command에 description()을 추가해 실행 로그를 남길 것
//         -> "로그로 기록"까지 커버하면 커맨드 패턴의 정의 3가지를 모두 만든 셈
//
// 생각해 볼 것
//   - undo 대상 상태가 커지면 커맨드 안에 상태를 들고 있기 부담스러워진다
//     -> 그때 메멘토 패턴과 짝지어 쓴다 (10_Memento 참고)

#include <iostream>

int main() {
	std::cout << "TODO: undo/redo 스택과 작업 큐를 구현해 보세요\n";
	return 0;
}
