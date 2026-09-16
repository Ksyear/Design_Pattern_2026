// [연습] 퍼사드 패턴 - 최소 지식 원칙 직접 위반해 보기
//
// 헤드 퍼스트 7장의 '뇌 단련' 문제를 C++로 옮긴 것.
//
// 아래 두 코드는 결과가 같다. 하지만 하나는 최소 지식 원칙(Law of Demeter)을 어긴다.
//
//   float getTemp() { return station.getThermometer().getTemperature(); }   // (A)
//   float getTemp() { Thermometer t = station.getThermometer(); return t.getTemperature(); } // (B)
//
// TODO 1. Station / Thermometer 클래스를 만들고 (A)와 (B)를 둘 다 써 볼 것
// TODO 2. 두 코드가 결합된 클래스 개수를 각각 세어 볼 것
//         (힌트: 줄을 나눈다고 결합이 줄지는 않는다 - 둘 다 2개다)
// TODO 3. Station에 getTemperature()를 직접 두어 결합을 1개로 줄일 것
//         -> 이게 바로 '퍼사드를 한 겹 두는 것'과 같은 발상
// TODO 4. HomeTheaterFacade가 없을 때 main이 몇 개 클래스와 얽히는지 세어 보고,
//         퍼사드를 넣었을 때와 비교할 것
//
// 최소 지식 원칙이 허용하는 메소드 호출 대상 4가지
//   1. 객체 자신
//   2. 메소드에 매개변수로 전달된 객체
//   3. 그 메소드가 생성하거나 인스턴스를 만든 객체
//   4. 그 객체에 속하는 구성 요소(인스턴스 변수)
//
// 주의: 이 원칙을 과하게 지키면 '전달만 하는(wrapper) 메소드'가 늘어나 복잡해진다
//       -> 원칙에도 트레이드오프가 있다는 점을 코드로 확인할 것

#include <iostream>

int main() {
	std::cout << "TODO: 최소 지식 원칙을 코드로 확인해 보세요\n";
	return 0;
}
