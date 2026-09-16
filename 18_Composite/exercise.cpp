// [연습] 컴포지트 패턴 - 파일 시스템 + 컴포지트 반복자
//
// 1단계: 기본 트리
// TODO 1. FileSystemNode(Component), File(Leaf), Directory(Composite)를 만들 것
// TODO 2. size()를 재귀로 구현 - Directory는 자식 크기의 합
// TODO 3. print(depth)로 트리를 들여쓰기 출력
//
// 2단계: 안전성 vs 투명성 직접 비교
// TODO 4. main.cpp는 '투명성'을 택해 Leaf::add()가 예외를 던진다.
//         이번엔 '안전성' 버전을 만들어 볼 것
//         - add/remove를 Directory에만 두고
//         - 클라이언트가 dynamic_cast<Directory*>로 확인하게 한다
// TODO 5. 두 방식의 클라이언트 코드를 나란히 놓고 어느 쪽이 읽기 쉬운지 판단할 것
//
// 3단계: 반복자와 결합 (헤드 퍼스트 9장이 실제로 하는 것)
// TODO 6. CompositeIterator를 만들 것
//         - 내부에 std::stack<Iterator*>를 두고 깊이 우선으로 트리를 평탄화한다
//         - 클라이언트는 while(it->hasNext()) 만 돌면 트리 전체를 훑는다
// TODO 7. 그 반복자로 "전체 트리에서 크기가 1MB 넘는 파일" 을 찾아볼 것
//
// 컴포지트가 단일 역할 원칙을 어긴다는 점
//   Menu는 '자식 관리'와 '메뉴 출력' 두 역할을 동시에 갖는다.
//   책은 이걸 "투명성을 얻기 위해 원칙 하나를 의도적으로 포기했다"고 인정한다.
//   -> 원칙은 규칙이 아니라 저울이다

#include <iostream>

int main() {
	std::cout << "TODO: 파일 시스템 컴포지트와 컴포지트 반복자를 만들어 보세요\n";
	return 0;
}
