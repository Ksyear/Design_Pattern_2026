// [연습] 데코레이터 패턴 - 헤드 퍼스트 3장 자바 I/O 흉내
//
// 자바의 InputStream 계층은 데코레이터 패턴 그 자체다.
// C++ 표준 스트림은 데코레이터가 아니므로, 직접 같은 구조를 만들어 본다.
//
// TODO 1. Component: struct CharSource { virtual int read() = 0; };  // EOF는 -1
// TODO 2. ConcreteComponent: StringSource - std::string을 한 글자씩 돌려준다
// TODO 3. Decorator(추상): SourceDecorator - CharSource를 unique_ptr로 감싼다
// TODO 4. ConcreteDecorator 두 개
//         - LowerCaseSource : 대문자를 소문자로 바꿔 돌려준다
//         - SkipSpaceSource : 공백은 건너뛰고 다음 글자를 돌려준다
// TODO 5. main에서 StringSource를 두 데코레이터로 감싸고, 감싸는 순서를 바꿔 보며
//         결과가 달라지는지 확인할 것 (데코레이터는 순서에 민감하다)

#include <iostream>

int main() {
	std::cout << "TODO: CharSource 데코레이터 체인을 만들어 보세요\n";
	return 0;
}
