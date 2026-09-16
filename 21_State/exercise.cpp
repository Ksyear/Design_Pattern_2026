// [연습] 상태 패턴 - 리필 기능과 상태 다이어그램 검증
//
// 1단계: 책 10장의 마지막 연습문제
// TODO 1. GumballMachine에 refill(int count)를 추가할 것
//         - 알맹이를 채우고, 매진 상태였다면 '동전 투입 대기' 상태로 돌아가야 한다
// TODO 2. refill을 State 인터페이스에 넣을지, Context에만 둘지 결정하고 이유를 적을 것
//         (힌트: 모든 상태에서 리필이 가능한가? 배출 중에 리필하면?)
//
// 2단계: 상태 다이어그램을 코드로 검증
// TODO 3. 아래 전이표를 코드로 표현하고, 모든 (상태, 이벤트) 조합을 실행해
//         실제 도달 상태가 표와 같은지 확인하는 테스트를 짤 것
//
//   상태\이벤트   | insertQuarter | ejectQuarter | turnCrank
//   -------------|---------------|--------------|-------------
//   NoQuarter    | HasQuarter    | NoQuarter    | NoQuarter
//   HasQuarter   | HasQuarter    | NoQuarter    | Sold/Winner
//   Sold         | Sold          | Sold         | Sold
//   SoldOut      | SoldOut       | SoldOut      | SoldOut
//
// 3단계: if/switch 버전과 비교
// TODO 4. 같은 기능을 enum + switch 한 덩어리로 구현해 볼 것 (책 10장 앞부분의 방식)
// TODO 5. 두 버전에 '알맹이 2개 뽑기 당첨' 상태를 추가해 보고
//         고쳐야 하는 메소드 수를 세어 비교할 것
//         -> 상태 패턴 쪽은 클래스 1개 추가 + 전이 지점 1곳
//            switch 쪽은 모든 메소드의 switch를 전부 고쳐야 한다
//
// 전략 패턴과 헷갈릴 때 쓰는 한 문장
//   "다음에 무엇이 올지 누가 아는가?"
//   클라이언트가 안다 -> 전략 / 상태 객체가 안다 -> 상태

#include <iostream>

int main() {
	std::cout << "TODO: 리필 기능과 상태 전이 테스트를 만들어 보세요\n";
	return 0;
}
