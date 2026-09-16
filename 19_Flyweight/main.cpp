// 플라이웨이트 패턴 (Flyweight) - 헤드 퍼스트 14장 조경 설계 앱의 나무 수천 그루
//
// 이 파일은 "조립과 호출"만 한다. 클래스는 기능별 폴더에 나뉘어 있다.
//   flyweight/  공유 대상 - TreeType.*(내부 상태만, 전부 const)
//   factory/    풀 관리   - TreeFactory.*(같은 키면 같은 객체를 돌려준다)
//   forest/     문맥      - Tree.*(외부 상태 + 참조) + Forest.*(컬렉션)
//
// 폴더가 갈리면 "무엇이 공유되고 무엇이 개별인가"가 한눈에 보인다.
// 결과: 나무 100만 그루를 만들어도 실제 TreeType 객체는 '종류 수'만큼만 존재한다.
#include <iostream>

#include "forest/Forest.h"

int main() {
	Forest forest;

	std::cout << "--- 나무 심는 중 (종류는 3가지뿐) ---\n";
	for (int i = 0; i < 4; ++i) forest.plantTree(i * 10, i * 5, 3 + i, "소나무", "진녹색", "거친껍질");
	for (int i = 0; i < 3; ++i) forest.plantTree(100 + i * 7, 40, 5, "단풍나무", "붉은색", "매끈함");
	for (int i = 0; i < 3; ++i) forest.plantTree(200 + i * 4, 80, 12, "벚나무", "분홍색", "얼룩무늬");

	std::cout << "\n--- 화면 그리기 (외부 상태는 그릴 때 넘긴다) ---\n";
	forest.draw();

	forest.report();

	std::cout << "\n--- 100만 그루로 늘려도 TreeType은 3개 그대로 ---\n";
	Forest big;
	for (int i = 0; i < 1000000; ++i) {
		big.plantTree(i % 1000, i / 1000, i % 30, "소나무", "진녹색", "거친껍질");
	}
	big.report();

	return 0;
}
