// [연습] 메멘토 패턴 - 커맨드와 짝지어 실전 undo 만들기
//
// 시나리오
//   간단한 텍스트 에디터. insert / deleteRange / replaceAll 명령을 지원한다.
//
// TODO 1. TextEditor를 오리지네이터로 만들고 Memento에 전체 문자열을 담을 것
// TODO 2. Command 인터페이스(09_Command 참고)의 각 구상 커맨드가
//         execute() 직전에 editor.save()를 호출해 메멘토를 들고 있게 할 것
// TODO 3. undo()는 들고 있던 메멘토로 editor.restore()만 하면 끝나게 할 것
//         -> 커맨드마다 '되돌리는 로직'을 따로 짜지 않아도 된다는 점을 체감
// TODO 4. 메모리 문제를 재현할 것
//         100만 글자 문서에서 한 글자 칠 때마다 전체를 스냅숏하면 어떻게 되는가?
//         -> refactoring.guru가 말하는 "잦은 스냅숏은 RAM을 많이 먹는다"
// TODO 5. 개선안을 하나 고르고 구현할 것
//         (a) 증분 메멘토: 바뀐 구간만 저장
//         (b) 스냅숏 개수 상한 + 오래된 것부터 폐기
//
// 생각해 볼 것
//   - 커맨드에 상태를 직접 넣는 방식(09_Command의 CeilingFanCommand)과
//     메멘토로 빼는 방식의 경계는 어디인가?
//     -> 되돌릴 상태가 '값 하나'면 커맨드에, '객체 전체'면 메멘토에

#include <iostream>

int main() {
	std::cout << "TODO: 커맨드 + 메멘토로 텍스트 에디터 undo를 만들어 보세요\n";
	return 0;
}
