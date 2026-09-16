// [연습] 브리지 패턴 - 클래스 폭발 직접 겪어 보기
//
// 1단계: 일부러 잘못 만들어 본다
// TODO 1. Shape를 상속으로만 확장해 볼 것
//         Circle, Square x Red, Blue -> RedCircle, BlueCircle, RedSquare, BlueSquare (4개)
// TODO 2. 색을 하나(Green) 추가하면 클래스가 몇 개가 되는지 세어 볼 것 (6개)
// TODO 3. 도형을 하나(Triangle) 더 추가하면? (9개)  -> M x N 폭발을 눈으로 확인
//
// 2단계: 브리지로 고친다
// TODO 4. Color 인터페이스(applyColor())를 만들고 Red/Blue/Green 구현
// TODO 5. Shape가 Color를 unique_ptr로 들고 있게 할 것 (추상화 -> 구현 위임)
// TODO 6. 이제 도형 3개 + 색 3개 = 6개 클래스로 9가지 조합이 되는지 확인
//
// 어댑터와의 차이 (자주 헷갈린다)
//   - 어댑터: 이미 만들어져 있는 것들을 '나중에' 붙인다
//   - 브리지: 두 축이 따로 커질 걸 알고 '미리' 떼어 둔다
//   구조가 비슷해도 설계 시점과 의도가 다르다

#include <iostream>

int main() {
	std::cout << "TODO: 도형 x 색 조합을 브리지로 분리해 보세요\n";
	return 0;
}
