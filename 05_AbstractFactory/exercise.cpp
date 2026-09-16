// [연습] 추상 팩토리 패턴 - GUI 위젯 제품군
//
// 시나리오
//   버튼과 체크박스를 macOS 스타일 / Windows 스타일로 각각 그려야 한다.
//   macOS 버튼과 Windows 체크박스가 섞이는 일은 절대 없어야 한다.
//
// TODO 1. Abstract Product : Button(paint()), Checkbox(paint())
// TODO 2. Concrete Product : MacButton/MacCheckbox, WinButton/WinCheckbox
// TODO 3. Abstract Factory : GUIFactory { createButton(); createCheckbox(); }
// TODO 4. Concrete Factory : MacFactory, WinFactory
// TODO 5. Client 함수 하나 - const GUIFactory& 만 받아서 화면을 그린다
//         (main에서 실행 인자나 #ifdef로 공장을 골라 넘길 것)
//
// 확인할 것
//   - 제품을 하나 더(예: TextField) 추가하면 어디를 고쳐야 하는가?
//     -> 추상 팩토리 인터페이스 + 모든 구상 팩토리 = 추상 팩토리의 대표적인 단점

#include <iostream>

int main() {
	std::cout << "TODO: macOS/Windows 위젯 제품군을 만들어 보세요\n";
	return 0;
}
