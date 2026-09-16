// [연습] 반복자 패턴 - 순회 알고리즘을 컬렉션에서 떼어내기
//
// 시나리오
//   18_Composite에서 만든 메뉴 트리를 여러 방식으로 훑고 싶다.
//
// TODO 1. 간단한 이진 트리를 만들 것 (struct Node { int v; Node* l; Node* r; })
// TODO 2. 반복자 3종을 각각 별도 클래스로 만들 것
//         - InOrderIterator, PreOrderIterator, BreadthFirstIterator
//         - 셋 다 hasNext()/next() 인터페이스는 동일
// TODO 3. 트리 클래스에는 순회 코드를 한 줄도 두지 말 것
//         -> "컬렉션은 항목 관리만, 반복은 반복자가" (단일 역할 원칙)
// TODO 4. 같은 트리에 대해 세 반복자를 동시에 돌려 결과를 나란히 출력할 것
//         -> 각 반복자가 자기 상태를 따로 들고 있다는 걸 확인
// TODO 5. STL 규약에 맞춰 begin()/end()를 추가해 범위 기반 for가 되게 할 것
//         필요한 것: operator++, operator*, operator!=
//
// 생각해 볼 것
//   - 순회 도중에 컬렉션이 수정되면 어떻게 되는가? (반복자 무효화)
//     STL도 같은 문제를 안고 있다. vector에 push_back하면 기존 반복자가 무효가 된다
//   - refactoring.guru가 말하는 단점 "단순 컬렉션에는 과하다"가 언제부터 맞는 말인가?

#include <iostream>

int main() {
	std::cout << "TODO: 트리 순회 반복자 3종을 만들어 보세요\n";
	return 0;
}
